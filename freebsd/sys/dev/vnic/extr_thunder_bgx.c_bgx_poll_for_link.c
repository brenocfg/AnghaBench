#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct lmac {int link_up; int last_speed; int last_duplex; int last_link; int /*<<< orphan*/  check_link; TYPE_1__* bgx; int /*<<< orphan*/  lmacid; } ;
struct TYPE_4__ {scalar_t__ lmac_type; } ;

/* Variables and functions */
 scalar_t__ BGX_MODE_XLAUI ; 
 int /*<<< orphan*/  BGX_SPUX_STATUS1 ; 
 int SPU_STATUS1_RCV_LNK ; 
 int /*<<< orphan*/  bgx_poll_reg (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  bgx_reg_modify (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int bgx_reg_read (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bgx_xaui_check_link (struct lmac*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,void (*) (void*),struct lmac*) ; 
 int hz ; 

__attribute__((used)) static void
bgx_poll_for_link(void *arg)
{
	struct lmac *lmac;
	uint64_t link;

	lmac = (struct lmac *)arg;

	/* Receive link is latching low. Force it high and verify it */
	bgx_reg_modify(lmac->bgx, lmac->lmacid,
		       BGX_SPUX_STATUS1, SPU_STATUS1_RCV_LNK);
	bgx_poll_reg(lmac->bgx, lmac->lmacid, BGX_SPUX_STATUS1,
		     SPU_STATUS1_RCV_LNK, false);

	link = bgx_reg_read(lmac->bgx, lmac->lmacid, BGX_SPUX_STATUS1);
	if (link & SPU_STATUS1_RCV_LNK) {
		lmac->link_up = 1;
		if (lmac->bgx->lmac_type == BGX_MODE_XLAUI)
			lmac->last_speed = 40000;
		else
			lmac->last_speed = 10000;
		lmac->last_duplex = 1;
	} else {
		lmac->link_up = 0;
	}

	if (lmac->last_link != lmac->link_up) {
		lmac->last_link = lmac->link_up;
		if (lmac->link_up)
			bgx_xaui_check_link(lmac);
	}

	callout_reset(&lmac->check_link, hz * 2, bgx_poll_for_link, lmac);
}