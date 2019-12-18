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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  brcmstb_gisb_arb_decode_addr (void*,char*) ; 

__attribute__((used)) static irqreturn_t brcmstb_gisb_timeout_handler(int irq, void *dev_id)
{
	brcmstb_gisb_arb_decode_addr(dev_id, "timeout");

	return IRQ_HANDLED;
}