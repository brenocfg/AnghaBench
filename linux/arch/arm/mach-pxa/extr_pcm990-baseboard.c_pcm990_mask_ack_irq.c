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
struct irq_data {int irq; } ;

/* Variables and functions */
 int PCM027_IRQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCM990_CTRL_INTMSKENA ; 
 int /*<<< orphan*/  pcm990_cpld_writeb (int,int /*<<< orphan*/ ) ; 
 int pcm990_irq_enabled ; 

__attribute__((used)) static void pcm990_mask_ack_irq(struct irq_data *d)
{
	int pcm990_irq = (d->irq - PCM027_IRQ(0));

	pcm990_irq_enabled &= ~(1 << pcm990_irq);

	pcm990_cpld_writeb(pcm990_irq_enabled, PCM990_CTRL_INTMSKENA);
}