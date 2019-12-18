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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
struct fman_qmi_regs {int /*<<< orphan*/  fmqm_gc; } ;

/* Variables and functions */
 int QMI_CFG_ENQ_MASK ; 
 int ioread32be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ *) ; 

void fman_set_qmi_enq_th(struct fman_qmi_regs *qmi_rg, uint8_t val)
{
	uint32_t tmp_reg;

	tmp_reg = ioread32be(&qmi_rg->fmqm_gc);
	tmp_reg &= ~QMI_CFG_ENQ_MASK;
	tmp_reg |= ((uint32_t)val << 8);
	iowrite32be(tmp_reg, &qmi_rg->fmqm_gc);
}