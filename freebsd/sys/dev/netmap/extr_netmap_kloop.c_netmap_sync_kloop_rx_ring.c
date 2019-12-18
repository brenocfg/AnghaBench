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
typedef  scalar_t__ uint32_t ;
struct sync_kloop_ring_args {scalar_t__ irq_ctx; scalar_t__ busy_wait; int /*<<< orphan*/  direct; struct nm_csb_ktoa* csb_ktoa; struct nm_csb_atok* csb_atok; struct netmap_kring* kring; } ;
struct nm_csb_ktoa {int dummy; } ;
struct nm_csb_atok {int dummy; } ;
struct netmap_ring {scalar_t__ tail; int /*<<< orphan*/  head; int /*<<< orphan*/  flags; } ;
struct netmap_kring {scalar_t__ nkr_num_slots; scalar_t__ rtail; int (* nm_sync ) (struct netmap_kring*,int /*<<< orphan*/ ) ;scalar_t__ rhead; int /*<<< orphan*/  nr_hwtail; int /*<<< orphan*/  nr_hwcur; } ;

/* Variables and functions */
 scalar_t__ NM_ACCESS_ONCE (int /*<<< orphan*/ ) ; 
 int NM_DEBUG_RXSYNC ; 
 int SYNC_LOOP_RX_DRY_CYCLES_MAX ; 
 scalar_t__ csb_atok_intr_enabled (struct nm_csb_atok*) ; 
 int /*<<< orphan*/  csb_ktoa_kick_enable (struct nm_csb_ktoa*,int) ; 
 int /*<<< orphan*/  eventfd_signal (scalar_t__,int) ; 
 int netmap_debug ; 
 int /*<<< orphan*/  netmap_ring_reinit (struct netmap_kring*) ; 
 int /*<<< orphan*/  nm_kr_put (struct netmap_kring*) ; 
 int nm_kr_tryget (struct netmap_kring*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nm_prdis (int,char*,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  nm_prerr (char*) ; 
 scalar_t__ nm_rxsync_prologue (struct netmap_kring*,struct netmap_ring*) ; 
 int /*<<< orphan*/  nm_stld_barrier () ; 
 int stub1 (struct netmap_kring*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync_kloop_kernel_read (struct nm_csb_atok*,struct netmap_ring*,scalar_t__) ; 
 int /*<<< orphan*/  sync_kloop_kernel_write (struct nm_csb_ktoa*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sync_kloop_kring_dump (char*,struct netmap_kring*) ; 
 scalar_t__ sync_kloop_norxslots (struct netmap_kring*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
netmap_sync_kloop_rx_ring(const struct sync_kloop_ring_args *a)
{

	struct netmap_kring *kring = a->kring;
	struct nm_csb_atok *csb_atok = a->csb_atok;
	struct nm_csb_ktoa *csb_ktoa = a->csb_ktoa;
	struct netmap_ring shadow_ring; /* shadow copy of the netmap_ring */
	int dry_cycles = 0;
	bool some_recvd = false;
	uint32_t num_slots;

	if (unlikely(nm_kr_tryget(kring, 1, NULL))) {
		return;
	}

	num_slots = kring->nkr_num_slots;

	/* Get RX csb_atok and csb_ktoa pointers from the CSB. */
	num_slots = kring->nkr_num_slots;

	/* Disable notifications. */
	if (!a->direct) {
		csb_ktoa_kick_enable(csb_ktoa, 0);
	}
	/* Copy the application kring pointers from the CSB */
	sync_kloop_kernel_read(csb_atok, &shadow_ring, num_slots);

	for (;;) {
		uint32_t hwtail;

		/* Netmap prologue */
		shadow_ring.tail = kring->rtail;
		if (unlikely(nm_rxsync_prologue(kring, &shadow_ring) >= num_slots)) {
			/* Reinit ring and enable notifications. */
			netmap_ring_reinit(kring);
			if (!a->busy_wait) {
				csb_ktoa_kick_enable(csb_ktoa, 1);
			}
			break;
		}

		if (unlikely(netmap_debug & NM_DEBUG_RXSYNC)) {
			sync_kloop_kring_dump("pre rxsync", kring);
		}

		if (unlikely(kring->nm_sync(kring, shadow_ring.flags))) {
			if (!a->busy_wait) {
				/* Reenable notifications. */
				csb_ktoa_kick_enable(csb_ktoa, 1);
			}
			nm_prerr("rxsync() failed");
			break;
		}

		/*
		 * Finalize
		 * Copy kernel hwcur and hwtail into the CSB for the application sync()
		 */
		hwtail = NM_ACCESS_ONCE(kring->nr_hwtail);
		sync_kloop_kernel_write(csb_ktoa, kring->nr_hwcur, hwtail);
		if (kring->rtail != hwtail) {
			kring->rtail = hwtail;
			some_recvd = true;
			dry_cycles = 0;
		} else {
			dry_cycles++;
		}

		if (unlikely(netmap_debug & NM_DEBUG_RXSYNC)) {
			sync_kloop_kring_dump("post rxsync", kring);
		}

#ifdef SYNC_KLOOP_POLL
		/* Interrupt the application if needed. */
		if (a->irq_ctx && some_recvd && csb_atok_intr_enabled(csb_atok)) {
			/* We could disable kernel --> application kicks here,
			 * to avoid spurious interrupts. */
			eventfd_signal(a->irq_ctx, 1);
			some_recvd = false;
		}
#endif /* SYNC_KLOOP_POLL */

		/* Read CSB to see if there is more work to do. */
		sync_kloop_kernel_read(csb_atok, &shadow_ring, num_slots);
		if (sync_kloop_norxslots(kring, shadow_ring.head)) {
			if (a->busy_wait) {
				break;
			}
			/*
			 * No more slots available for reception. We enable notification and
			 * go to sleep, waiting for a kick from the application when new receive
			 * slots are available.
			 */
			/* Reenable notifications. */
			csb_ktoa_kick_enable(csb_ktoa, 1);
			/* Double check, with store-load memory barrier. */
			nm_stld_barrier();
			sync_kloop_kernel_read(csb_atok, &shadow_ring, num_slots);
			if (!sync_kloop_norxslots(kring, shadow_ring.head)) {
				/* We won the race condition, more slots are available. Disable
				 * notifications and do another cycle. */
				csb_ktoa_kick_enable(csb_ktoa, 0);
				continue;
			}
			break;
		}

		hwtail = NM_ACCESS_ONCE(kring->nr_hwtail);
		if (unlikely(hwtail == kring->rhead ||
					dry_cycles >= SYNC_LOOP_RX_DRY_CYCLES_MAX)) {
			/* No more packets to be read from the backend. We stop and
			 * wait for a notification from the backend (netmap_rx_irq). */
			nm_prdis(1, "nr_hwtail: %d rhead: %d dry_cycles: %d",
					hwtail, kring->rhead, dry_cycles);
			break;
		}
	}

	nm_kr_put(kring);

#ifdef SYNC_KLOOP_POLL
	/* Interrupt the application if needed. */
	if (a->irq_ctx && some_recvd && csb_atok_intr_enabled(csb_atok)) {
		eventfd_signal(a->irq_ctx, 1);
	}
#endif /* SYNC_KLOOP_POLL */
}