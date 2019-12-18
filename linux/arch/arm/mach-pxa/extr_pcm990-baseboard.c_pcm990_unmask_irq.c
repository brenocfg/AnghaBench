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
typedef  int u8 ;
struct irq_data {int irq; } ;

/* Variables and functions */
 int PCM027_IRQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCM990_CTRL_INTMSKENA ; 
 int /*<<< orphan*/  PCM990_CTRL_INTSETCLR ; 
 int pcm990_cpld_readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcm990_cpld_writeb (int,int /*<<< orphan*/ ) ; 
 int pcm990_irq_enabled ; 

__attribute__((used)) static void pcm990_unmask_irq(struct irq_data *d)
{
	int pcm990_irq = (d->irq - PCM027_IRQ(0));
	u8 val;

	/* the irq can be acknowledged only if deasserted, so it's done here */

	pcm990_irq_enabled |= (1 << pcm990_irq);

	val = pcm990_cpld_readb(PCM990_CTRL_INTSETCLR);
	val |= 1 << pcm990_irq;
	pcm990_cpld_writeb(val, PCM990_CTRL_INTSETCLR);

	pcm990_cpld_writeb(pcm990_irq_enabled, PCM990_CTRL_INTMSKENA);
}