#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ hdb3; } ;
struct TYPE_11__ {int /*<<< orphan*/  lx; TYPE_1__ gopt; TYPE_3__* board; scalar_t__ num; } ;
typedef  TYPE_4__ ct_chan_t ;
struct TYPE_9__ {scalar_t__ cfg; } ;
struct TYPE_10__ {TYPE_2__ opt; } ;

/* Variables and functions */
 scalar_t__ CFG_B ; 
 int /*<<< orphan*/  LX_CCR1 ; 
 int /*<<< orphan*/  LX_CCR2 ; 
 int /*<<< orphan*/  LX_CCR2_LH ; 
 int /*<<< orphan*/  LX_CCR3 ; 
 int /*<<< orphan*/  LX_CCR3_E1_LH ; 
 int /*<<< orphan*/  LX_HDB3 ; 
 int /*<<< orphan*/  LX_LOS ; 
 int /*<<< orphan*/  LX_RESET ; 
 int /*<<< orphan*/  LX_TAOS ; 
 int /*<<< orphan*/  ctg_inx (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctg_outx (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ct_setup_lxt (ct_chan_t *c)
{
	ctg_outx (c, LX_CCR1, LX_RESET); 	/* reset the chip */
	/* Delay */
	ctg_inx (c, LX_CCR1);
	c->lx = LX_LOS; 		/* disable loss of sync interrupt */
	if (c->num && c->board->opt.cfg == CFG_B)
		c->lx |= LX_TAOS;	/* idle channel--transmit all ones */
	if (c->gopt.hdb3)
		c->lx |= LX_HDB3;	/* enable HDB3 encoding */
	ctg_outx (c, LX_CCR1, c->lx);		/* setup the new mode */
	ctg_outx (c, LX_CCR2, LX_CCR2_LH);	/* setup Long Haul mode */
	ctg_outx (c, LX_CCR3, LX_CCR3_E1_LH);	/* setup Long Haul mode */
}