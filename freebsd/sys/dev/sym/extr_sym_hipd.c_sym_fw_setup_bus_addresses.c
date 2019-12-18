#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_short ;
typedef  scalar_t__ u32 ;
struct sym_fw {scalar_t__ b_ofs; scalar_t__ a_ofs; } ;
typedef  TYPE_1__* hcb_p ;
struct TYPE_3__ {scalar_t__ const scriptb_ba; int /*<<< orphan*/  fwb_bas; scalar_t__ const scripta_ba; int /*<<< orphan*/  fwa_bas; } ;

/* Variables and functions */

__attribute__((used)) static void
sym_fw_setup_bus_addresses(hcb_p np, const struct sym_fw *fw)
{
	u32 *pa;
	const u_short *po;
	int i;

	/*
	 *  Build the bus address table for script A
	 *  from the script A offset table.
	 */
	po = (const u_short *) fw->a_ofs;
	pa = (u32 *) &np->fwa_bas;
	for (i = 0 ; i < sizeof(np->fwa_bas)/sizeof(u32) ; i++)
		pa[i] = np->scripta_ba + po[i];

	/*
	 *  Same for script B.
	 */
	po = (const u_short *) fw->b_ofs;
	pa = (u32 *) &np->fwb_bas;
	for (i = 0 ; i < sizeof(np->fwb_bas)/sizeof(u32) ; i++)
		pa[i] = np->scriptb_ba + po[i];
}