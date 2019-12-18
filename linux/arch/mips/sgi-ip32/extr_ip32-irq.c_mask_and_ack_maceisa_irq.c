#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct irq_data {int irq; } ;
struct TYPE_4__ {unsigned long istat; } ;
struct TYPE_5__ {TYPE_1__ ctrl; } ;
struct TYPE_6__ {TYPE_2__ perif; } ;

/* Variables and functions */
 int MACEISA_AUDIO_SW_IRQ ; 
 int /*<<< orphan*/  disable_maceisa_irq (struct irq_data*) ; 
 TYPE_3__* mace ; 

__attribute__((used)) static void mask_and_ack_maceisa_irq(struct irq_data *d)
{
	unsigned long mace_int;

	/* edge triggered */
	mace_int = mace->perif.ctrl.istat;
	mace_int &= ~(1 << (d->irq - MACEISA_AUDIO_SW_IRQ));
	mace->perif.ctrl.istat = mace_int;

	disable_maceisa_irq(d);
}