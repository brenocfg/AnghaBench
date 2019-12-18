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
struct irq_data {scalar_t__ irq; } ;
typedef  int /*<<< orphan*/ * irq_flow_handler_t ;

/* Variables and functions */
 scalar_t__ ALCHEMY_GPIC_INT_BASE ; 
 int EINVAL ; 
 unsigned long GPIC_CFG_IC_EDGE_BOTH ; 
 unsigned long GPIC_CFG_IC_EDGE_FALL ; 
 unsigned long GPIC_CFG_IC_EDGE_RISE ; 
 unsigned long GPIC_CFG_IC_LEVEL_HIGH ; 
 unsigned long GPIC_CFG_IC_LEVEL_LOW ; 
 int /*<<< orphan*/  GPIC_CFG_IC_MASK ; 
 unsigned long GPIC_CFG_IC_OFF ; 
#define  IRQ_TYPE_EDGE_BOTH 133 
#define  IRQ_TYPE_EDGE_FALLING 132 
#define  IRQ_TYPE_EDGE_RISING 131 
#define  IRQ_TYPE_LEVEL_HIGH 130 
#define  IRQ_TYPE_LEVEL_LOW 129 
#define  IRQ_TYPE_NONE 128 
 int /*<<< orphan*/  au1300_gpic ; 
 int /*<<< orphan*/  au1300_gpic_chgcfg (scalar_t__,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/ * handle_edge_irq ; 
 int /*<<< orphan*/ * handle_level_irq ; 
 int /*<<< orphan*/  irq_set_chip_handler_name_locked (struct irq_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char*) ; 

__attribute__((used)) static int au1300_gpic_settype(struct irq_data *d, unsigned int type)
{
	unsigned long s;
	unsigned char *name = NULL;
	irq_flow_handler_t hdl = NULL;

	switch (type) {
	case IRQ_TYPE_LEVEL_HIGH:
		s = GPIC_CFG_IC_LEVEL_HIGH;
		name = "high";
		hdl = handle_level_irq;
		break;
	case IRQ_TYPE_LEVEL_LOW:
		s = GPIC_CFG_IC_LEVEL_LOW;
		name = "low";
		hdl = handle_level_irq;
		break;
	case IRQ_TYPE_EDGE_RISING:
		s = GPIC_CFG_IC_EDGE_RISE;
		name = "posedge";
		hdl = handle_edge_irq;
		break;
	case IRQ_TYPE_EDGE_FALLING:
		s = GPIC_CFG_IC_EDGE_FALL;
		name = "negedge";
		hdl = handle_edge_irq;
		break;
	case IRQ_TYPE_EDGE_BOTH:
		s = GPIC_CFG_IC_EDGE_BOTH;
		name = "bothedge";
		hdl = handle_edge_irq;
		break;
	case IRQ_TYPE_NONE:
		s = GPIC_CFG_IC_OFF;
		name = "disabled";
		hdl = handle_level_irq;
		break;
	default:
		return -EINVAL;
	}

	irq_set_chip_handler_name_locked(d, &au1300_gpic, hdl, name);

	au1300_gpic_chgcfg(d->irq - ALCHEMY_GPIC_INT_BASE, GPIC_CFG_IC_MASK, s);

	return 0;
}