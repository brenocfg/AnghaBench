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
typedef  int /*<<< orphan*/  etherswitch_vlangroup_t ;
typedef  int /*<<< orphan*/  e6000sw_softc_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  E6000SW_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  E6000SW_LOCK_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E6000SW_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SA_UNLOCKED ; 
 int /*<<< orphan*/ * device_get_softc (int /*<<< orphan*/ ) ; 
 int e6000sw_setvgroup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
e6000sw_setvgroup_wrapper(device_t dev, etherswitch_vlangroup_t *vg)
{
	e6000sw_softc_t *sc;
	int ret;

	sc = device_get_softc(dev);
	E6000SW_LOCK_ASSERT(sc, SA_UNLOCKED);

	E6000SW_LOCK(sc);
	ret = e6000sw_setvgroup(dev, vg);
	E6000SW_UNLOCK(sc);

	return (ret);
}