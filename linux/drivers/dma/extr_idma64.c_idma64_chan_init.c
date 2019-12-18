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
struct idma64_chan {int /*<<< orphan*/  mask; } ;
struct idma64 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG_HI ; 
 int /*<<< orphan*/  CFG_LO ; 
 int /*<<< orphan*/  ERROR ; 
 int IDMA64C_CFGH_DST_PER (int /*<<< orphan*/ ) ; 
 int IDMA64C_CFGH_SRC_PER (int) ; 
 int IDMA64C_CFGL_DST_BURST_ALIGN ; 
 int IDMA64C_CFGL_SRC_BURST_ALIGN ; 
 int /*<<< orphan*/  MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFER ; 
 int /*<<< orphan*/  channel_set_bit (struct idma64*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  channel_writel (struct idma64_chan*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  idma64_on (struct idma64*) ; 

__attribute__((used)) static void idma64_chan_init(struct idma64 *idma64, struct idma64_chan *idma64c)
{
	u32 cfghi = IDMA64C_CFGH_SRC_PER(1) | IDMA64C_CFGH_DST_PER(0);
	u32 cfglo = 0;

	/* Set default burst alignment */
	cfglo |= IDMA64C_CFGL_DST_BURST_ALIGN | IDMA64C_CFGL_SRC_BURST_ALIGN;

	channel_writel(idma64c, CFG_LO, cfglo);
	channel_writel(idma64c, CFG_HI, cfghi);

	/* Enable interrupts */
	channel_set_bit(idma64, MASK(XFER), idma64c->mask);
	channel_set_bit(idma64, MASK(ERROR), idma64c->mask);

	/*
	 * Enforce the controller to be turned on.
	 *
	 * The iDMA is turned off in ->probe() and looses context during system
	 * suspend / resume cycle. That's why we have to enable it each time we
	 * use it.
	 */
	idma64_on(idma64);
}