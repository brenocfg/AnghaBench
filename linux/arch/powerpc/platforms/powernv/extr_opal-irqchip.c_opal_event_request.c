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
struct TYPE_2__ {int /*<<< orphan*/  domain; } ;

/* Variables and functions */
 scalar_t__ WARN_ON_ONCE (int) ; 
 int irq_create_mapping (int /*<<< orphan*/ ,unsigned int) ; 
 TYPE_1__ opal_event_irqchip ; 

int opal_event_request(unsigned int opal_event_nr)
{
	if (WARN_ON_ONCE(!opal_event_irqchip.domain))
		return 0;

	return irq_create_mapping(opal_event_irqchip.domain, opal_event_nr);
}