#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int cfg; scalar_t__ clk0; scalar_t__ clk1; } ;
struct TYPE_5__ {int /*<<< orphan*/  e1cfg; int /*<<< orphan*/  port; scalar_t__ chan; TYPE_1__ opt; } ;
typedef  TYPE_2__ ct_board_t ;

/* Variables and functions */
#define  CFG_B 130 
#define  CFG_C 129 
#define  CFG_D 128 
 int /*<<< orphan*/  E1CFG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1CFG_CLK0_INT ; 
 int /*<<< orphan*/  E1CFG_CLK0_RCLK1 ; 
 int /*<<< orphan*/  E1CFG_CLK0_RCV ; 
 int /*<<< orphan*/  E1CFG_CLK1_INT ; 
 int /*<<< orphan*/  E1CFG_CLK1_RCLK0 ; 
 int /*<<< orphan*/  E1CFG_CLK1_RCV ; 
 int /*<<< orphan*/  E1CFG_D ; 
 int /*<<< orphan*/  E1CFG_GRUN ; 
 int /*<<< orphan*/  E1CFG_HI ; 
 int /*<<< orphan*/  E1CFG_II ; 
 int /*<<< orphan*/  E1CFG_K ; 
 int /*<<< orphan*/  E1CFG_LED ; 
 scalar_t__ GCLK_RCLKO ; 
 scalar_t__ GCLK_RCV ; 
 int /*<<< orphan*/  ct_setup_ctlr (scalar_t__) ; 
 int /*<<< orphan*/  ct_setup_scc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ct_setup_e1 (ct_board_t *b)
{
	/*
	 * Control register 0:
	 * 1) board configuration
	 * 2) clock modes
	 */
	b->e1cfg &= E1CFG_LED;
	switch (b->opt.cfg){
	case CFG_C: b->e1cfg |= E1CFG_K;  break;
	case CFG_B: b->e1cfg |= E1CFG_HI; break;
	case CFG_D: b->e1cfg |= E1CFG_D;  break;
	default:    b->e1cfg |= E1CFG_II; break;
	}

	if (b->opt.clk0 == GCLK_RCV)   b->e1cfg |= E1CFG_CLK0_RCV;
	if (b->opt.clk0 == GCLK_RCLKO) b->e1cfg |= E1CFG_CLK0_RCLK1;
	else			       b->e1cfg |= E1CFG_CLK0_INT;
	if (b->opt.clk1 == GCLK_RCV)   b->e1cfg |= E1CFG_CLK1_RCV;
	if (b->opt.clk1 == GCLK_RCLKO) b->e1cfg |= E1CFG_CLK1_RCLK0;
	else			       b->e1cfg |= E1CFG_CLK1_INT;

	outb (E1CFG (b->port), b->e1cfg);

	/*
	 * Set up serial controller.
	 */
	ct_setup_scc (b->port);

	/*
	 * Set up E1 controllers.
	 */
	ct_setup_ctlr (b->chan + 0);	/* channel 0 */
	ct_setup_ctlr (b->chan + 1);	/* channel 1 */

	/* Start the board (GRUN). */
	b->e1cfg |= E1CFG_GRUN;
	outb (E1CFG (b->port), b->e1cfg);
}