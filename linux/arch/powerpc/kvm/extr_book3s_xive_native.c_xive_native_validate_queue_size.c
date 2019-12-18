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
typedef  int u32 ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int xive_native_validate_queue_size(u32 qshift)
{
	/*
	 * We only support 64K pages for the moment. This is also
	 * advertised in the DT property "ibm,xive-eq-sizes"
	 */
	switch (qshift) {
	case 0: /* EQ reset */
	case 16:
		return 0;
	case 12:
	case 21:
	case 24:
	default:
		return -EINVAL;
	}
}