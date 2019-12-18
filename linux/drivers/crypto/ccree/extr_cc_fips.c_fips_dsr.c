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
typedef  int u32 ;
struct cc_drvdata {int irq; } ;

/* Variables and functions */
 int CC_GPR0_IRQ_MASK ; 
 int CC_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HOST_IMR ; 
 int /*<<< orphan*/  cc_iowrite (struct cc_drvdata*,int,int) ; 
 int /*<<< orphan*/  cc_tee_handle_fips_error (struct cc_drvdata*) ; 

__attribute__((used)) static void fips_dsr(unsigned long devarg)
{
	struct cc_drvdata *drvdata = (struct cc_drvdata *)devarg;
	u32 irq, val;

	irq = (drvdata->irq & (CC_GPR0_IRQ_MASK));

	if (irq) {
		cc_tee_handle_fips_error(drvdata);
	}

	/* after verifing that there is nothing to do,
	 * unmask AXI completion interrupt.
	 */
	val = (CC_REG(HOST_IMR) & ~irq);
	cc_iowrite(drvdata, CC_REG(HOST_IMR), val);
}