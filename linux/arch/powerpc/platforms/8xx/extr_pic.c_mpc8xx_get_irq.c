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
struct TYPE_2__ {int /*<<< orphan*/  sc_sivec; } ;

/* Variables and functions */
 int PIC_VEC_SPURRIOUS ; 
 int in_be32 (int /*<<< orphan*/ *) ; 
 unsigned int irq_linear_revmap (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mpc8xx_pic_host ; 
 TYPE_1__* siu_reg ; 

unsigned int mpc8xx_get_irq(void)
{
	int irq;

	/* For MPC8xx, read the SIVEC register and shift the bits down
	 * to get the irq number.
	 */
	irq = in_be32(&siu_reg->sc_sivec) >> 26;

	if (irq == PIC_VEC_SPURRIOUS)
		return 0;

        return irq_linear_revmap(mpc8xx_pic_host, irq);

}