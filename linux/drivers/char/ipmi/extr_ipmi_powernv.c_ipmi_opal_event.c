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
struct ipmi_smi_powernv {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  ipmi_powernv_recv (struct ipmi_smi_powernv*) ; 

__attribute__((used)) static irqreturn_t ipmi_opal_event(int irq, void *data)
{
	struct ipmi_smi_powernv *smi = data;

	ipmi_powernv_recv(smi);
	return IRQ_HANDLED;
}