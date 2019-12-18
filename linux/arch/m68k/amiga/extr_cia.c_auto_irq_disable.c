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
struct irq_data {int irq; } ;
struct TYPE_2__ {int /*<<< orphan*/  intena; } ;

/* Variables and functions */
 int /*<<< orphan*/  IF_EXTER ; 
 int /*<<< orphan*/  IF_PORTS ; 
#define  IRQ_AUTO_2 129 
#define  IRQ_AUTO_6 128 
 TYPE_1__ amiga_custom ; 

__attribute__((used)) static void auto_irq_disable(struct irq_data *data)
{
	switch (data->irq) {
	case IRQ_AUTO_2:
		amiga_custom.intena = IF_PORTS;
		break;
	case IRQ_AUTO_6:
		amiga_custom.intena = IF_EXTER;
		break;
	}
}