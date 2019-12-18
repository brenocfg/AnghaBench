#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nasid_t ;
struct TYPE_2__ {int iprb_ovflow; int iprb_ff; int iprb_xtalkctr; int /*<<< orphan*/  iprb_regval; scalar_t__ iprb_anakctr; scalar_t__ iprb_bnakctr; } ;
typedef  TYPE_1__ iprb_t ;

/* Variables and functions */
 int IIO_IOPRB (int) ; 
 int /*<<< orphan*/  REMOTE_HUB_L (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REMOTE_HUB_S (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ force_fire_and_forget ; 

__attribute__((used)) static void hub_setup_prb(nasid_t nasid, int prbnum, int credits)
{
	iprb_t prb;
	int prb_offset;

	/*
	 * Get the current register value.
	 */
	prb_offset = IIO_IOPRB(prbnum);
	prb.iprb_regval = REMOTE_HUB_L(nasid, prb_offset);

	/*
	 * Clear out some fields.
	 */
	prb.iprb_ovflow = 1;
	prb.iprb_bnakctr = 0;
	prb.iprb_anakctr = 0;

	/*
	 * Enable or disable fire-and-forget mode.
	 */
	prb.iprb_ff = force_fire_and_forget ? 1 : 0;

	/*
	 * Set the appropriate number of PIO credits for the widget.
	 */
	prb.iprb_xtalkctr = credits;

	/*
	 * Store the new value to the register.
	 */
	REMOTE_HUB_S(nasid, prb_offset, prb.iprb_regval);
}