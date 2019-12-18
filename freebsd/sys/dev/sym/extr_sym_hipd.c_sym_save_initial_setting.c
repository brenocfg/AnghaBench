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
typedef  TYPE_1__* hcb_p ;
struct TYPE_3__ {int sv_scntl0; int sv_scntl3; int sv_dmode; int sv_dcntl; int sv_ctest3; int sv_ctest4; int sv_gpcntl; int sv_stest1; int sv_stest2; int sv_stest4; int features; int sv_scntl4; int sv_ctest5; } ;

/* Variables and functions */
 int FE_C10 ; 
 int INB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nc_ctest3 ; 
 int /*<<< orphan*/  nc_ctest4 ; 
 int /*<<< orphan*/  nc_ctest5 ; 
 int /*<<< orphan*/  nc_dcntl ; 
 int /*<<< orphan*/  nc_dmode ; 
 int /*<<< orphan*/  nc_gpcntl ; 
 int /*<<< orphan*/  nc_scntl0 ; 
 int /*<<< orphan*/  nc_scntl3 ; 
 int /*<<< orphan*/  nc_scntl4 ; 
 int /*<<< orphan*/  nc_stest1 ; 
 int /*<<< orphan*/  nc_stest2 ; 
 int /*<<< orphan*/  nc_stest4 ; 

__attribute__((used)) static void sym_save_initial_setting (hcb_p np)
{
	np->sv_scntl0	= INB(nc_scntl0) & 0x0a;
	np->sv_scntl3	= INB(nc_scntl3) & 0x07;
	np->sv_dmode	= INB(nc_dmode)  & 0xce;
	np->sv_dcntl	= INB(nc_dcntl)  & 0xa8;
	np->sv_ctest3	= INB(nc_ctest3) & 0x01;
	np->sv_ctest4	= INB(nc_ctest4) & 0x80;
	np->sv_gpcntl	= INB(nc_gpcntl);
	np->sv_stest1	= INB(nc_stest1);
	np->sv_stest2	= INB(nc_stest2) & 0x20;
	np->sv_stest4	= INB(nc_stest4);
	if (np->features & FE_C10) {	/* Always large DMA fifo + ultra3 */
		np->sv_scntl4	= INB(nc_scntl4);
		np->sv_ctest5	= INB(nc_ctest5) & 0x04;
	}
	else
		np->sv_ctest5	= INB(nc_ctest5) & 0x24;
}