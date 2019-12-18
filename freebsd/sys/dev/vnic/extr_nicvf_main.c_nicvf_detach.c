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
struct nicvf {int /*<<< orphan*/  ifp; int /*<<< orphan*/  if_media; int /*<<< orphan*/ * reg_base; int /*<<< orphan*/  stats_mtx; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  NICVF_CORE_LOCK (struct nicvf*) ; 
 int /*<<< orphan*/  NICVF_CORE_LOCK_DESTROY (struct nicvf*) ; 
 int /*<<< orphan*/  NICVF_CORE_UNLOCK (struct nicvf*) ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct nicvf* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifmedia_removeall (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nicvf_release_all_interrupts (struct nicvf*) ; 
 int /*<<< orphan*/  nicvf_stop_locked (struct nicvf*) ; 
 int /*<<< orphan*/  rman_get_rid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nicvf_detach(device_t dev)
{
	struct nicvf *nic;

	nic = device_get_softc(dev);

	NICVF_CORE_LOCK(nic);
	/* Shut down the port and release ring resources */
	nicvf_stop_locked(nic);
	/* Release stats lock */
	mtx_destroy(&nic->stats_mtx);
	/* Release interrupts */
	nicvf_release_all_interrupts(nic);
	/* Release memory resource */
	if (nic->reg_base != NULL) {
		bus_release_resource(dev, SYS_RES_MEMORY,
		    rman_get_rid(nic->reg_base), nic->reg_base);
	}

	/* Remove all ifmedia configurations */
	ifmedia_removeall(&nic->if_media);
	/* Free this ifnet */
	if_free(nic->ifp);
	NICVF_CORE_UNLOCK(nic);
	/* Finally destroy the lock */
	NICVF_CORE_LOCK_DESTROY(nic);

	return (0);
}