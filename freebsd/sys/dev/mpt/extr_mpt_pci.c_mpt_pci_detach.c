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
struct mpt_softc {int /*<<< orphan*/ * eh; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_DEREGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MPT_LOCK_DESTROY (struct mpt_softc*) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_detach (struct mpt_softc*) ; 
 int /*<<< orphan*/  mpt_disable_ints (struct mpt_softc*) ; 
 int /*<<< orphan*/  mpt_dma_mem_free (struct mpt_softc*) ; 
 int /*<<< orphan*/  mpt_free_bus_resources (struct mpt_softc*) ; 
 int /*<<< orphan*/  mpt_raid_free_mem (struct mpt_softc*) ; 
 int /*<<< orphan*/  mpt_reset (struct mpt_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_unlink_peer (struct mpt_softc*) ; 
 int /*<<< orphan*/  shutdown_post_sync ; 

__attribute__((used)) static int
mpt_pci_detach(device_t dev)
{
	struct mpt_softc *mpt;

	mpt  = (struct mpt_softc*)device_get_softc(dev);

	if (mpt) {
		mpt_disable_ints(mpt);
		mpt_detach(mpt);
		mpt_reset(mpt, /*reinit*/FALSE);
		mpt_raid_free_mem(mpt);
		mpt_dma_mem_free(mpt);
		mpt_free_bus_resources(mpt);
#if 0
		mpt_unlink_peer(mpt);
#endif
		if (mpt->eh != NULL) {
                        EVENTHANDLER_DEREGISTER(shutdown_post_sync, mpt->eh);
		}
		MPT_LOCK_DESTROY(mpt);
	}
	return(0);
}