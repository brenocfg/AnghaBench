#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32_t ;
struct sync_kloop_ring_args {scalar_t__ irq_ctx; scalar_t__ busy_wait; int /*<<< orphan*/  direct; struct nm_csb_ktoa* csb_ktoa; struct nm_csb_atok* csb_atok; struct netmap_kring* kring; } ;
struct nm_csb_ktoa {int dummy; } ;
struct nm_csb_atok {int dummy; } ;
struct netmap_ring {int head; scalar_t__ tail; int /*<<< orphan*/  flags; } ;
struct netmap_kring {int nkr_num_slots; int nr_hwcur; scalar_t__ rtail; int (* nm_sync ) (struct netmap_kring*,int /*<<< orphan*/ ) ;scalar_t__ nr_hwtail; scalar_t__ rhead; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAF_FORCE_RECLAIM ; 
 int NM_DEBUG_TXSYNC ; 
 int PTN_TX_BATCH_LIM (int) ; 
 scalar_t__ csb_atok_intr_enabled (struct nm_csb_atok*) ; 
 int /*<<< orphan*/  csb_ktoa_kick_enable (struct nm_csb_ktoa*,int) ; 
 int /*<<< orphan*/  eventfd_signal (scalar_t__,int) ; 
 int netmap_debug ; 
 int /*<<< orphan*/  netmap_ring_reinit (struct netmap_kring*) ; 
 int /*<<< orphan*/  nm_kr_put (struct netmap_kring*) ; 
 int nm_kr_tryget (struct netmap_kring*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ nm_kr_txempty (struct netmap_kring*) ; 
 int nm_kr_txspace (struct netmap_kring*) ; 
 int /*<<< orphan*/  nm_prdis (int,char*,...) ; 
 int /*<<< orphan*/  nm_prerr (char*) ; 
 int /*<<< orphan*/  nm_stld_barrier () ; 
 int nm_txsync_prologue (struct netmap_kring*,struct netmap_ring*) ; 
 int stub1 (struct netmap_kring*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync_kloop_kernel_read (struct nm_csb_atok*,struct netmap_ring*,int) ; 
 int /*<<< orphan*/  sync_kloop_kernel_write (struct nm_csb_ktoa*,int,scalar_t__) ; 
 int /*<<< orphan*/  sync_kloop_kring_dump (char*,struct netmap_kring*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
netmap_sync_kloop_tx_ring(const struct sync_kloop_ring_args *a)
{
	struct netmap_kring *kring = a->kring;
	struct nm_csb_atok *csb_atok = a->csb_atok;
	struct nm_csb_ktoa *csb_ktoa = a->csb_ktoa;
	struct netmap_ring shadow_ring; /* shadow copy of the netmap_ring */
	bool more_txspace = false;
	uint32_t num_slots;
	int batch;

	if (unlikely(nm_kr_tryget(kring, 1, NULL))) {
		return;
	}

	num_slots = kring->nkr_num_slots;

	/* Disable application --> kernel notifications. */
	if (!a->direct) {
		csb_ktoa_kick_enable(csb_ktoa, 0);
	}
	/* Copy the application kring pointers from the CSB */
	sync_kloop_kernel_read(csb_atok, &shadow_ring, num_slots);

	for (;;) {
		batch = shadow_ring.head - kring->nr_hwcur;
		if (batch < 0)
			batch += num_slots;

#ifdef PTN_TX_BATCH_LIM
		if (batch > PTN_TX_BATCH_LIM(num_slots)) {
			/* If application moves ahead too fast, let's cut the move so
			 * that we don't exceed our batch limit. */
			uint32_t head_lim = kring->nr_hwcur + PTN_TX_BATCH_LIM(num_slots);

			if (head_lim >= num_slots)
				head_lim -= num_slots;
			nm_prdis(1, "batch: %d head: %d head_lim: %d", batch, shadow_ring.head,
					head_lim);
			shadow_ring.head = head_lim;
			batch = PTN_TX_BATCH_LIM(num_slots);
		}
#endif /* PTN_TX_BATCH_LIM */

		if (nm_kr_txspace(kring) <= (num_slots >> 1)) {
			shadow_ring.flags |= NAF_FORCE_RECLAIM;
		}

		/* Netmap prologue */
		shadow_ring.tail = kring->rtail;
		if (unlikely(nm_txsync_prologue(kring, &shadow_ring) >= num_slots)) {
			/* Reinit ring and enable notifications. */
			netmap_ring_reinit(kring);
			if (!a->busy_wait) {
				csb_ktoa_kick_enable(csb_ktoa, 1);
			}
			break;
		}

		if (unlikely(netmap_debug & NM_DEBUG_TXSYNC)) {
			sync_kloop_kring_dump("pre txsync", kring);
		}

		if (unlikely(kring->nm_sync(kring, shadow_ring.flags))) {
			if (!a->busy_wait) {
				/* Reenable notifications. */
				csb_ktoa_kick_enable(csb_ktoa, 1);
			}
			nm_prerr("txsync() failed");
			break;
		}

		/*
		 * Finalize
		 * Copy kernel hwcur and hwtail into the CSB for the application sync(), and
		 * do the nm_sync_finalize.
		 */
		sync_kloop_kernel_write(csb_ktoa, kring->nr_hwcur,
				kring->nr_hwtail);
		if (kring->rtail != kring->nr_hwtail) {
			/* Some more room available in the parent adapter. */
			kring->rtail = kring->nr_hwtail;
			more_txspace = true;
		}

		if (unlikely(netmap_debug & NM_DEBUG_TXSYNC)) {
			sync_kloop_kring_dump("post txsync", kring);
		}

		/* Interrupt the application if needed. */
#ifdef SYNC_KLOOP_POLL
		if (a->irq_ctx && more_txspace && csb_atok_intr_enabled(csb_atok)) {
			/* We could disable kernel --> application kicks here,
			 * to avoid spurious interrupts. */
			eventfd_signal(a->irq_ctx, 1);
			more_txspace = false;
		}
#endif /* SYNC_KLOOP_POLL */

		/* Read CSB to see if there is more work to do. */
		sync_kloop_kernel_read(csb_atok, &shadow_ring, num_slots);
		if (shadow_ring.head == kring->rhead) {
			if (a->busy_wait) {
				break;
			}
			/*
			 * No more packets to transmit. We enable notifications and
			 * go to sleep, waiting for a kick from the application when new
			 * new slots are ready for transmission.
			 */
			/* Reenable notifications. */
			csb_ktoa_kick_enable(csb_ktoa, 1);
			/* Double check, with store-load memory barrier. */
			nm_stld_barrier();
			sync_kloop_kernel_read(csb_atok, &shadow_ring, num_slots);
			if (shadow_ring.head != kring->rhead) {
				/* We won the race condition, there are more packets to
				 * transmit. Disable notifications and do another cycle */
				csb_ktoa_kick_enable(csb_ktoa, 0);
				continue;
			}
			break;
		}

		if (nm_kr_txempty(kring)) {
			/* No more available TX slots. We stop waiting for a notification
			 * from the backend (netmap_tx_irq). */
			nm_prdis(1, "TX ring");
			break;
		}
	}

	nm_kr_put(kring);

#ifdef SYNC_KLOOP_POLL
	if (a->irq_ctx && more_txspace && csb_atok_intr_enabled(csb_atok)) {
		eventfd_signal(a->irq_ctx, 1);
	}
#endif /* SYNC_KLOOP_POLL */
}