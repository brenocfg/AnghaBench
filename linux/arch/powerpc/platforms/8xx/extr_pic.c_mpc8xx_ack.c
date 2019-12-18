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
struct irq_data {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sc_sipend; } ;

/* Variables and functions */
 int /*<<< orphan*/  mpc8xx_irqd_to_bit (struct irq_data*) ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* siu_reg ; 

__attribute__((used)) static void mpc8xx_ack(struct irq_data *d)
{
	out_be32(&siu_reg->sc_sipend, mpc8xx_irqd_to_bit(d));
}