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
struct TYPE_2__ {void (* handler ) (void*) ;void* data; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOENT ; 
 int /*<<< orphan*/  dmabrg_enable_irq (unsigned int) ; 
 TYPE_1__* dmabrg_handlers ; 

int dmabrg_request_irq(unsigned int dmairq, void(*handler)(void*),
		       void *data)
{
	if ((dmairq > 9) || !handler)
		return -ENOENT;
	if (dmabrg_handlers[dmairq].handler)
		return -EBUSY;

	dmabrg_handlers[dmairq].handler = handler;
	dmabrg_handlers[dmairq].data = data;
	
	dmabrg_enable_irq(dmairq);
	return 0;
}