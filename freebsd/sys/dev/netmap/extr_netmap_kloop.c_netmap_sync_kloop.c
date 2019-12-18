#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct sync_kloop_ring_args {int busy_wait; int direct; int num_entries; int num_tx_rings; int num_rings; int next_entry; struct sync_kloop_poll_entry* entries; int /*<<< orphan*/  wait_table; int /*<<< orphan*/ * next_wake_fun; struct file* irq_ctx; struct nm_csb_ktoa* csb_ktoa; struct nm_csb_atok* csb_atok; void* kring; } ;
struct sync_kloop_poll_entry {scalar_t__ filp; scalar_t__ irq_filp; struct file* irq_ctx; int /*<<< orphan*/  wait; scalar_t__ wqh; struct sync_kloop_ring_args* args; struct sync_kloop_ring_args* parent; } ;
struct sync_kloop_poll_ctx {int busy_wait; int direct; int num_entries; int num_tx_rings; int num_rings; int next_entry; struct sync_kloop_poll_entry* entries; int /*<<< orphan*/  wait_table; int /*<<< orphan*/ * next_wake_fun; struct file* irq_ctx; struct nm_csb_ktoa* csb_ktoa; struct nm_csb_atok* csb_atok; void* kring; } ;
struct nmreq_sync_kloop_start {int sleep_us; } ;
struct nmreq_option {int nro_status; int nro_size; } ;
struct nmreq_opt_sync_kloop_mode {int mode; } ;
struct nmreq_opt_sync_kloop_eventfds {TYPE_1__* eventfds; } ;
struct nmreq_header {scalar_t__ nr_body; } ;
struct nm_csb_ktoa {int dummy; } ;
struct nm_csb_atok {int dummy; } ;
struct netmap_priv_d {int np_kloop_state; int* np_qlast; int* np_qfirst; scalar_t__ np_filp; int /*<<< orphan*/ * np_si; struct nm_csb_ktoa* np_csb_ktoa_base; struct nm_csb_atok* np_csb_atok_base; struct netmap_adapter* np_na; int /*<<< orphan*/ * np_nifp; } ;
struct netmap_adapter {int na_flags; int /*<<< orphan*/  name; } ;
struct file {TYPE_2__* f_op; } ;
struct eventfd_ctx {TYPE_2__* f_op; } ;
typedef  int /*<<< orphan*/  args ;
struct TYPE_4__ {unsigned long (* poll ) (struct file*,int /*<<< orphan*/ *) ;} ;
struct TYPE_3__ {scalar_t__ ioeventfd; scalar_t__ irqfd; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENXIO ; 
 int EOPNOTSUPP ; 
 scalar_t__ IS_ERR (struct file*) ; 
 int NAF_BDG_MAYSLEEP ; 
 int /*<<< orphan*/  NETMAP_REQ_OPT_SYNC_KLOOP_EVENTFDS ; 
 int /*<<< orphan*/  NETMAP_REQ_OPT_SYNC_KLOOP_MODE ; 
 int /*<<< orphan*/  NMG_LOCK () ; 
 int /*<<< orphan*/  NMG_UNLOCK () ; 
 void** NMR (struct netmap_adapter*,size_t) ; 
 int NM_ACCESS_ONCE (int) ; 
 int NM_OPT_SYNC_KLOOP_DIRECT_RX ; 
 int NM_OPT_SYNC_KLOOP_DIRECT_TX ; 
 int NM_SYNC_KLOOP_RUNNING ; 
 int NM_SYNC_KLOOP_STOPPING ; 
 size_t NR_RX ; 
 size_t NR_TX ; 
 unsigned long POLLERR ; 
 int PTR_ERR (struct file*) ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 struct file* eventfd_ctx_fileget (struct file*) ; 
 int /*<<< orphan*/  eventfd_ctx_put (struct file*) ; 
 struct file* eventfd_fget (scalar_t__) ; 
 int /*<<< orphan*/  fput (scalar_t__) ; 
 int /*<<< orphan*/  init_poll_funcptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  netmap_sync_kloop_rx_ring (struct sync_kloop_ring_args*) ; 
 int /*<<< orphan*/  netmap_sync_kloop_tx_ring (struct sync_kloop_ring_args*) ; 
 int /*<<< orphan*/  nm_netmap_on (struct netmap_adapter*) ; 
 int /*<<< orphan*/  nm_os_free (struct sync_kloop_ring_args*) ; 
 struct sync_kloop_ring_args* nm_os_malloc (int) ; 
 int /*<<< orphan*/  nm_prerr (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nm_prinf (char*,int,int,int,int) ; 
 struct nmreq_option* nmreq_getoption (struct nmreq_header*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poll_wait (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_wait_queue (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 unsigned long stub1 (struct file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sync_kloop_poll_table_queue_proc ; 
 int /*<<< orphan*/ * sync_kloop_rx_irq_wake_fun ; 
 int /*<<< orphan*/ * sync_kloop_rx_kick_wake_fun ; 
 int /*<<< orphan*/ * sync_kloop_tx_irq_wake_fun ; 
 int /*<<< orphan*/ * sync_kloop_tx_kick_wake_fun ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

int
netmap_sync_kloop(struct netmap_priv_d *priv, struct nmreq_header *hdr)
{
	struct nmreq_sync_kloop_start *req =
		(struct nmreq_sync_kloop_start *)(uintptr_t)hdr->nr_body;
	struct nmreq_opt_sync_kloop_eventfds *eventfds_opt = NULL;
#ifdef SYNC_KLOOP_POLL
	struct sync_kloop_poll_ctx *poll_ctx = NULL;
#endif  /* SYNC_KLOOP_POLL */
	int num_rx_rings, num_tx_rings, num_rings;
	struct sync_kloop_ring_args *args = NULL;
	uint32_t sleep_us = req->sleep_us;
	struct nm_csb_atok* csb_atok_base;
	struct nm_csb_ktoa* csb_ktoa_base;
	struct netmap_adapter *na;
	struct nmreq_option *opt;
	bool na_could_sleep = false;
	bool busy_wait = true;
	bool direct_tx = false;
	bool direct_rx = false;
	int err = 0;
	int i;

	if (sleep_us > 1000000) {
		/* We do not accept sleeping for more than a second. */
		return EINVAL;
	}

	if (priv->np_nifp == NULL) {
		return ENXIO;
	}
	mb(); /* make sure following reads are not from cache */

	na = priv->np_na;
	if (!nm_netmap_on(na)) {
		return ENXIO;
	}

	NMG_LOCK();
	/* Make sure the application is working in CSB mode. */
	if (!priv->np_csb_atok_base || !priv->np_csb_ktoa_base) {
		NMG_UNLOCK();
		nm_prerr("sync-kloop on %s requires "
				"NETMAP_REQ_OPT_CSB option", na->name);
		return EINVAL;
	}

	csb_atok_base = priv->np_csb_atok_base;
	csb_ktoa_base = priv->np_csb_ktoa_base;

	/* Make sure that no kloop is currently running. */
	if (priv->np_kloop_state & NM_SYNC_KLOOP_RUNNING) {
		err = EBUSY;
	}
	priv->np_kloop_state |= NM_SYNC_KLOOP_RUNNING;
	NMG_UNLOCK();
	if (err) {
		return err;
	}

	num_rx_rings = priv->np_qlast[NR_RX] - priv->np_qfirst[NR_RX];
	num_tx_rings = priv->np_qlast[NR_TX] - priv->np_qfirst[NR_TX];
	num_rings = num_tx_rings + num_rx_rings;

	args = nm_os_malloc(num_rings * sizeof(args[0]));
	if (!args) {
		err = ENOMEM;
		goto out;
	}

	/* Prepare the arguments for netmap_sync_kloop_tx_ring()
	 * and netmap_sync_kloop_rx_ring(). */
	for (i = 0; i < num_tx_rings; i++) {
		struct sync_kloop_ring_args *a = args + i;

		a->kring = NMR(na, NR_TX)[i + priv->np_qfirst[NR_TX]];
		a->csb_atok = csb_atok_base + i;
		a->csb_ktoa = csb_ktoa_base + i;
		a->busy_wait = busy_wait;
		a->direct = direct_tx;
	}
	for (i = 0; i < num_rx_rings; i++) {
		struct sync_kloop_ring_args *a = args + num_tx_rings + i;

		a->kring = NMR(na, NR_RX)[i + priv->np_qfirst[NR_RX]];
		a->csb_atok = csb_atok_base + num_tx_rings + i;
		a->csb_ktoa = csb_ktoa_base + num_tx_rings + i;
		a->busy_wait = busy_wait;
		a->direct = direct_rx;
	}

	/* Validate notification options. */
	opt = nmreq_getoption(hdr, NETMAP_REQ_OPT_SYNC_KLOOP_MODE);
	if (opt != NULL) {
		struct nmreq_opt_sync_kloop_mode *mode_opt =
		    (struct nmreq_opt_sync_kloop_mode *)opt;

		direct_tx = !!(mode_opt->mode & NM_OPT_SYNC_KLOOP_DIRECT_TX);
		direct_rx = !!(mode_opt->mode & NM_OPT_SYNC_KLOOP_DIRECT_RX);
		if (mode_opt->mode & ~(NM_OPT_SYNC_KLOOP_DIRECT_TX |
		    NM_OPT_SYNC_KLOOP_DIRECT_RX)) {
			opt->nro_status = err = EINVAL;
			goto out;
		}
		opt->nro_status = 0;
	}
	opt = nmreq_getoption(hdr, NETMAP_REQ_OPT_SYNC_KLOOP_EVENTFDS);
	if (opt != NULL) {
		if (opt->nro_size != sizeof(*eventfds_opt) +
			sizeof(eventfds_opt->eventfds[0]) * num_rings) {
			/* Option size not consistent with the number of
			 * entries. */
			opt->nro_status = err = EINVAL;
			goto out;
		}
#ifdef SYNC_KLOOP_POLL
		eventfds_opt = (struct nmreq_opt_sync_kloop_eventfds *)opt;
		opt->nro_status = 0;

		/* Check if some ioeventfd entry is not defined, and force sleep
		 * synchronization in that case. */
		busy_wait = false;
		for (i = 0; i < num_rings; i++) {
			if (eventfds_opt->eventfds[i].ioeventfd < 0) {
				busy_wait = true;
				break;
			}
		}

		if (busy_wait && (direct_tx || direct_rx)) {
			/* For direct processing we need all the
			 * ioeventfds to be valid. */
			opt->nro_status = err = EINVAL;
			goto out;
		}

		/* We need 2 poll entries for TX and RX notifications coming
		 * from the netmap adapter, plus one entries per ring for the
		 * notifications coming from the application. */
		poll_ctx = nm_os_malloc(sizeof(*poll_ctx) +
				(num_rings + 2) * sizeof(poll_ctx->entries[0]));
		init_poll_funcptr(&poll_ctx->wait_table,
					sync_kloop_poll_table_queue_proc);
		poll_ctx->num_entries = 2 + num_rings;
		poll_ctx->num_tx_rings = num_tx_rings;
		poll_ctx->num_rings = num_rings;
		poll_ctx->next_entry = 0;
		poll_ctx->next_wake_fun = NULL;

		if (direct_tx && (na->na_flags & NAF_BDG_MAYSLEEP)) {
			/* In direct mode, VALE txsync is called from
			 * wake-up context, where it is not possible
			 * to sleep.
			 */
			na->na_flags &= ~NAF_BDG_MAYSLEEP;
			na_could_sleep = true;
		}

		for (i = 0; i < num_rings + 2; i++) {
			poll_ctx->entries[i].args = args + i;
			poll_ctx->entries[i].parent = poll_ctx;
		}

		/* Poll for notifications coming from the applications through
		 * eventfds. */
		for (i = 0; i < num_rings; i++, poll_ctx->next_entry++) {
			struct eventfd_ctx *irq = NULL;
			struct file *filp = NULL;
			unsigned long mask;
			bool tx_ring = (i < num_tx_rings);

			if (eventfds_opt->eventfds[i].irqfd >= 0) {
				filp = eventfd_fget(
				    eventfds_opt->eventfds[i].irqfd);
				if (IS_ERR(filp)) {
					err = PTR_ERR(filp);
					goto out;
				}
				irq = eventfd_ctx_fileget(filp);
				if (IS_ERR(irq)) {
					err = PTR_ERR(irq);
					goto out;
				}
			}
			poll_ctx->entries[i].irq_filp = filp;
			poll_ctx->entries[i].irq_ctx = irq;
			poll_ctx->entries[i].args->busy_wait = busy_wait;
			/* Don't let netmap_sync_kloop_*x_ring() use
			 * IRQs in direct mode. */
			poll_ctx->entries[i].args->irq_ctx =
			    ((tx_ring && direct_tx) ||
			    (!tx_ring && direct_rx)) ? NULL :
			    poll_ctx->entries[i].irq_ctx;
			poll_ctx->entries[i].args->direct =
			    (tx_ring ? direct_tx : direct_rx);

			if (!busy_wait) {
				filp = eventfd_fget(
				    eventfds_opt->eventfds[i].ioeventfd);
				if (IS_ERR(filp)) {
					err = PTR_ERR(filp);
					goto out;
				}
				if (tx_ring && direct_tx) {
					/* Override the wake up function
					 * so that it can directly call
					 * netmap_sync_kloop_tx_ring().
					 */
					poll_ctx->next_wake_fun =
					    sync_kloop_tx_kick_wake_fun;
				} else if (!tx_ring && direct_rx) {
					/* Same for direct RX. */
					poll_ctx->next_wake_fun =
					    sync_kloop_rx_kick_wake_fun;
				} else {
					poll_ctx->next_wake_fun = NULL;
				}
				mask = filp->f_op->poll(filp,
				    &poll_ctx->wait_table);
				if (mask & POLLERR) {
					err = EINVAL;
					goto out;
				}
			}
		}

		/* Poll for notifications coming from the netmap rings bound to
		 * this file descriptor. */
		if (!busy_wait) {
			NMG_LOCK();
			/* In direct mode, override the wake up function so
			 * that it can forward the netmap_tx_irq() to the
			 * guest. */
			poll_ctx->next_wake_fun = direct_tx ?
			    sync_kloop_tx_irq_wake_fun : NULL;
			poll_wait(priv->np_filp, priv->np_si[NR_TX],
			    &poll_ctx->wait_table);
			poll_ctx->next_entry++;

			poll_ctx->next_wake_fun = direct_rx ?
			    sync_kloop_rx_irq_wake_fun : NULL;
			poll_wait(priv->np_filp, priv->np_si[NR_RX],
			    &poll_ctx->wait_table);
			poll_ctx->next_entry++;
			NMG_UNLOCK();
		}
#else   /* SYNC_KLOOP_POLL */
		opt->nro_status = EOPNOTSUPP;
		goto out;
#endif  /* SYNC_KLOOP_POLL */
	}

	nm_prinf("kloop busy_wait %u, direct_tx %u, direct_rx %u, "
	    "na_could_sleep %u", busy_wait, direct_tx, direct_rx,
	    na_could_sleep);

	/* Main loop. */
	for (;;) {
		if (unlikely(NM_ACCESS_ONCE(priv->np_kloop_state) & NM_SYNC_KLOOP_STOPPING)) {
			break;
		}

#ifdef SYNC_KLOOP_POLL
		if (!busy_wait) {
			/* It is important to set the task state as
			 * interruptible before processing any TX/RX ring,
			 * so that if a notification on ring Y comes after
			 * we have processed ring Y, but before we call
			 * schedule(), we don't miss it. This is true because
			 * the wake up function will change the the task state,
			 * and therefore the schedule_timeout() call below
			 * will observe the change).
			 */
			set_current_state(TASK_INTERRUPTIBLE);
		}
#endif  /* SYNC_KLOOP_POLL */

		/* Process all the TX rings bound to this file descriptor. */
		for (i = 0; !direct_tx && i < num_tx_rings; i++) {
			struct sync_kloop_ring_args *a = args + i;
			netmap_sync_kloop_tx_ring(a);
		}

		/* Process all the RX rings bound to this file descriptor. */
		for (i = 0; !direct_rx && i < num_rx_rings; i++) {
			struct sync_kloop_ring_args *a = args + num_tx_rings + i;
			netmap_sync_kloop_rx_ring(a);
		}

		if (busy_wait) {
			/* Default synchronization method: sleep for a while. */
			usleep_range(sleep_us, sleep_us);
		}
#ifdef SYNC_KLOOP_POLL
		else {
			/* Yield to the scheduler waiting for a notification
			 * to come either from netmap or the application. */
			schedule_timeout(msecs_to_jiffies(3000));
		}
#endif /* SYNC_KLOOP_POLL */
	}
out:
#ifdef SYNC_KLOOP_POLL
	if (poll_ctx) {
		/* Stop polling from netmap and the eventfds, and deallocate
		 * the poll context. */
		if (!busy_wait) {
			__set_current_state(TASK_RUNNING);
		}
		for (i = 0; i < poll_ctx->next_entry; i++) {
			struct sync_kloop_poll_entry *entry =
						poll_ctx->entries + i;

			if (entry->wqh)
				remove_wait_queue(entry->wqh, &entry->wait);
			/* We did not get a reference to the eventfds, but
			 * don't do that on netmap file descriptors (since
			 * a reference was not taken. */
			if (entry->filp && entry->filp != priv->np_filp)
				fput(entry->filp);
			if (entry->irq_ctx)
				eventfd_ctx_put(entry->irq_ctx);
			if (entry->irq_filp)
				fput(entry->irq_filp);
		}
		nm_os_free(poll_ctx);
		poll_ctx = NULL;
	}
#endif /* SYNC_KLOOP_POLL */

	if (args) {
		nm_os_free(args);
		args = NULL;
	}

	/* Reset the kloop state. */
	NMG_LOCK();
	priv->np_kloop_state = 0;
	if (na_could_sleep) {
		na->na_flags |= NAF_BDG_MAYSLEEP;
	}
	NMG_UNLOCK();

	return err;
}