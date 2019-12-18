#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct ahc_tmode_tstate {int /*<<< orphan*/  auto_negotiate; } ;
struct ahc_softc {int features; } ;
struct TYPE_4__ {scalar_t__ period; scalar_t__ width; scalar_t__ offset; scalar_t__ ppr_options; } ;
struct TYPE_3__ {scalar_t__ width; scalar_t__ period; scalar_t__ offset; scalar_t__ ppr_options; } ;
struct ahc_initiator_tinfo {TYPE_2__ goal; TYPE_1__ curr; } ;
struct ahc_devinfo {int /*<<< orphan*/  target_mask; } ;
typedef  scalar_t__ ahc_neg_type ;

/* Variables and functions */
 scalar_t__ AHC_NEG_ALWAYS ; 
 scalar_t__ AHC_NEG_IF_NON_ASYNC ; 
 scalar_t__ AHC_OFFSET_UNKNOWN ; 
 scalar_t__ AHC_PERIOD_UNKNOWN ; 
 int AHC_WIDE ; 
 scalar_t__ AHC_WIDTH_UNKNOWN ; 
 scalar_t__ MSG_EXT_WDTR_BUS_8_BIT ; 

int
ahc_update_neg_request(struct ahc_softc *ahc, struct ahc_devinfo *devinfo,
		       struct ahc_tmode_tstate *tstate,
		       struct ahc_initiator_tinfo *tinfo, ahc_neg_type neg_type)
{
	u_int auto_negotiate_orig;

	auto_negotiate_orig = tstate->auto_negotiate;
	if (neg_type == AHC_NEG_ALWAYS) {
		/*
		 * Force our "current" settings to be
		 * unknown so that unless a bus reset
		 * occurs the need to renegotiate is
		 * recorded persistently.
		 */
		if ((ahc->features & AHC_WIDE) != 0)
			tinfo->curr.width = AHC_WIDTH_UNKNOWN;
		tinfo->curr.period = AHC_PERIOD_UNKNOWN;
		tinfo->curr.offset = AHC_OFFSET_UNKNOWN;
	}
	if (tinfo->curr.period != tinfo->goal.period
	 || tinfo->curr.width != tinfo->goal.width
	 || tinfo->curr.offset != tinfo->goal.offset
	 || tinfo->curr.ppr_options != tinfo->goal.ppr_options
	 || (neg_type == AHC_NEG_IF_NON_ASYNC
	  && (tinfo->goal.offset != 0
	   || tinfo->goal.width != MSG_EXT_WDTR_BUS_8_BIT
	   || tinfo->goal.ppr_options != 0)))
		tstate->auto_negotiate |= devinfo->target_mask;
	else
		tstate->auto_negotiate &= ~devinfo->target_mask;

	return (auto_negotiate_orig != tstate->auto_negotiate);
}