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
struct timer16_priv {int total_cycles; scalar_t__ mapcommon; int /*<<< orphan*/  ovf; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ TISRC ; 
 int /*<<< orphan*/  bclr (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t timer16_interrupt(int irq, void *dev_id)
{
	struct timer16_priv *p = (struct timer16_priv *)dev_id;

	bclr(p->ovf, p->mapcommon + TISRC);
	p->total_cycles += 0x10000;

	return IRQ_HANDLED;
}