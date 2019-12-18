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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  driver_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/ * BUS_ADD_CHILD (int /*<<< orphan*/ ,int,char*,int) ; 
#define  IBM970FX 130 
#define  IBM970GX 129 
#define  IBM970MP 128 
 int /*<<< orphan*/ * device_find_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int mfpvr () ; 

__attribute__((used)) static void
pcr_identify(driver_t *driver, device_t parent)
{
	uint16_t vers;
	vers = mfpvr() >> 16;

	/* Check for an IBM 970-class CPU */
	switch (vers) {
		case IBM970FX:
		case IBM970GX:
		case IBM970MP:
			break;
		default:
			return;
	}

	/* Make sure we're not being doubly invoked. */
	if (device_find_child(parent, "pcr", -1) != NULL)
		return;

	/*
	 * We attach a child for every CPU since settings need to
	 * be performed on every CPU in the SMP case.
	 */
	if (BUS_ADD_CHILD(parent, 10, "pcr", -1) == NULL)
		device_printf(parent, "add pcr child failed\n");
}