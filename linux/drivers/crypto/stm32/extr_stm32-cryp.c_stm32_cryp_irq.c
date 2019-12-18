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
struct stm32_cryp {int /*<<< orphan*/  irq_status; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  CRYP_MISR ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int /*<<< orphan*/  stm32_cryp_read (struct stm32_cryp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t stm32_cryp_irq(int irq, void *arg)
{
	struct stm32_cryp *cryp = arg;

	cryp->irq_status = stm32_cryp_read(cryp, CRYP_MISR);

	return IRQ_WAKE_THREAD;
}