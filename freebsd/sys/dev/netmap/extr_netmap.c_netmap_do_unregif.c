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
struct netmap_priv_d {int /*<<< orphan*/ * np_nifp; struct netmap_adapter* np_na; } ;
struct netmap_adapter {scalar_t__ active_fds; int na_flags; int num_host_tx_rings; int num_host_rx_rings; int /*<<< orphan*/  (* nm_krings_delete ) (struct netmap_adapter*) ;int /*<<< orphan*/  name; int /*<<< orphan*/  (* nm_register ) (struct netmap_adapter*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int NAF_HOST_RINGS ; 
 int /*<<< orphan*/  NMG_LOCK_ASSERT () ; 
 int NM_DEBUG_ON ; 
 int netmap_debug ; 
 int /*<<< orphan*/  netmap_krings_put (struct netmap_priv_d*) ; 
 int /*<<< orphan*/  netmap_mem_drop (struct netmap_adapter*) ; 
 int /*<<< orphan*/  netmap_mem_if_delete (struct netmap_adapter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netmap_mem_rings_delete (struct netmap_adapter*) ; 
 int /*<<< orphan*/  netmap_monitor_stop (struct netmap_adapter*) ; 
 int /*<<< orphan*/  netmap_unset_ringid (struct netmap_priv_d*) ; 
 scalar_t__ nm_kring_pending (struct netmap_priv_d*) ; 
 scalar_t__ nm_netmap_on (struct netmap_adapter*) ; 
 int /*<<< orphan*/  nm_prerr (char*) ; 
 int /*<<< orphan*/  nm_prinf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct netmap_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct netmap_adapter*) ; 

void
netmap_do_unregif(struct netmap_priv_d *priv)
{
	struct netmap_adapter *na = priv->np_na;

	NMG_LOCK_ASSERT();
	na->active_fds--;
	/* unset nr_pending_mode and possibly release exclusive mode */
	netmap_krings_put(priv);

#ifdef	WITH_MONITOR
	/* XXX check whether we have to do something with monitor
	 * when rings change nr_mode. */
	if (na->active_fds <= 0) {
		/* walk through all the rings and tell any monitor
		 * that the port is going to exit netmap mode
		 */
		netmap_monitor_stop(na);
	}
#endif

	if (na->active_fds <= 0 || nm_kring_pending(priv)) {
		na->nm_register(na, 0);
	}

	/* delete rings and buffers that are no longer needed */
	netmap_mem_rings_delete(na);

	if (na->active_fds <= 0) {	/* last instance */
		/*
		 * (TO CHECK) We enter here
		 * when the last reference to this file descriptor goes
		 * away. This means we cannot have any pending poll()
		 * or interrupt routine operating on the structure.
		 * XXX The file may be closed in a thread while
		 * another thread is using it.
		 * Linux keeps the file opened until the last reference
		 * by any outstanding ioctl/poll or mmap is gone.
		 * FreeBSD does not track mmap()s (but we do) and
		 * wakes up any sleeping poll(). Need to check what
		 * happens if the close() occurs while a concurrent
		 * syscall is running.
		 */
		if (netmap_debug & NM_DEBUG_ON)
			nm_prinf("deleting last instance for %s", na->name);

		if (nm_netmap_on(na)) {
			nm_prerr("BUG: netmap on while going to delete the krings");
		}

		na->nm_krings_delete(na);

		/* restore the default number of host tx and rx rings */
		if (na->na_flags & NAF_HOST_RINGS) {
			na->num_host_tx_rings = 1;
			na->num_host_rx_rings = 1;
		} else {
			na->num_host_tx_rings = 0;
			na->num_host_rx_rings = 0;
		}
	}

	/* possibily decrement counter of tx_si/rx_si users */
	netmap_unset_ringid(priv);
	/* delete the nifp */
	netmap_mem_if_delete(na, priv->np_nifp);
	/* drop the allocator */
	netmap_mem_drop(na);
	/* mark the priv as unregistered */
	priv->np_na = NULL;
	priv->np_nifp = NULL;
}