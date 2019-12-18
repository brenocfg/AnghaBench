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
typedef  int u16 ;

/* Variables and functions */
 int PNV_OCXL_ACTAG_MAX ; 

__attribute__((used)) static u16 assign_fn_actags(u16 desired, u16 total)
{
	u16 count;

	if (total <= PNV_OCXL_ACTAG_MAX)
		count = desired;
	else
		count = PNV_OCXL_ACTAG_MAX * desired / total;

	return count;
}