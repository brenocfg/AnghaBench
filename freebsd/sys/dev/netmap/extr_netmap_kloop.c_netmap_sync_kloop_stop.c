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
struct netmap_priv_d {int /*<<< orphan*/  np_kloop_state; int /*<<< orphan*/ * np_si; struct netmap_adapter* np_na; int /*<<< orphan*/ * np_nifp; } ;
struct netmap_adapter {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  NMG_LOCK () ; 
 int /*<<< orphan*/  NMG_UNLOCK () ; 
 int NM_ACCESS_ONCE (int /*<<< orphan*/ ) ; 
 int NM_SYNC_KLOOP_RUNNING ; 
 int /*<<< orphan*/  NM_SYNC_KLOOP_STOPPING ; 
 size_t NR_RX ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  nm_netmap_on (struct netmap_adapter*) ; 
 int /*<<< orphan*/  nm_os_selwakeup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

int
netmap_sync_kloop_stop(struct netmap_priv_d *priv)
{
	struct netmap_adapter *na;
	bool running = true;
	int err = 0;

	if (priv->np_nifp == NULL) {
		return ENXIO;
	}
	mb(); /* make sure following reads are not from cache */

	na = priv->np_na;
	if (!nm_netmap_on(na)) {
		return ENXIO;
	}

	/* Set the kloop stopping flag. */
	NMG_LOCK();
	priv->np_kloop_state |= NM_SYNC_KLOOP_STOPPING;
	NMG_UNLOCK();

	/* Send a notification to the kloop, in case it is blocked in
	 * schedule_timeout(). We can use either RX or TX, because the
	 * kloop is waiting on both. */
	nm_os_selwakeup(priv->np_si[NR_RX]);

	/* Wait for the kloop to actually terminate. */
	while (running) {
		usleep_range(1000, 1500);
		NMG_LOCK();
		running = (NM_ACCESS_ONCE(priv->np_kloop_state)
				& NM_SYNC_KLOOP_RUNNING);
		NMG_UNLOCK();
	}

	return err;
}