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
struct tdfx_softc {int /*<<< orphan*/  mrdesc; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int MEMRANGE_SET_REMOVE ; 
 struct tdfx_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int mem_range_attr_set (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int
tdfx_clrmtrr(device_t dev) {
	/* This function removes the MTRR set by the attach call, so it can be used
	 * in the future by other drivers. 
	 */
	int retval, act;
	struct tdfx_softc *tdfx_info = device_get_softc(dev);
	
	act = MEMRANGE_SET_REMOVE;
	retval = mem_range_attr_set(&tdfx_info->mrdesc, &act);
	return retval;
}