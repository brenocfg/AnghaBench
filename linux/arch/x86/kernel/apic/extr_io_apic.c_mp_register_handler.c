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
typedef  int /*<<< orphan*/  irq_flow_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_LEVEL ; 
 int /*<<< orphan*/  __irq_set_handler (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  handle_fasteoi_irq ; 
 int /*<<< orphan*/  irq_clear_status_flags (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_status_flags (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mp_register_handler(unsigned int irq, unsigned long trigger)
{
	irq_flow_handler_t hdl;
	bool fasteoi;

	if (trigger) {
		irq_set_status_flags(irq, IRQ_LEVEL);
		fasteoi = true;
	} else {
		irq_clear_status_flags(irq, IRQ_LEVEL);
		fasteoi = false;
	}

	hdl = fasteoi ? handle_fasteoi_irq : handle_edge_irq;
	__irq_set_handler(irq, hdl, 0, fasteoi ? "fasteoi" : "edge");
}