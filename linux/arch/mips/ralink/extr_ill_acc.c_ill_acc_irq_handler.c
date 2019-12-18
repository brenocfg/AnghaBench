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
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int ILL_ACC_ID_M ; 
 int ILL_ACC_ID_S ; 
 int ILL_ACC_LEN_M ; 
 int ILL_ACC_OFF_M ; 
 int ILL_ACC_OFF_S ; 
 int ILL_ACC_WRITE ; 
 int /*<<< orphan*/  ILL_INT_STATUS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  REG_ILL_ACC_ADDR ; 
 int /*<<< orphan*/  REG_ILL_ACC_TYPE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,char*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/ * ill_acc_ids ; 
 int rt_memc_r32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt_memc_w32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t ill_acc_irq_handler(int irq, void *_priv)
{
	struct device *dev = (struct device *) _priv;
	u32 addr = rt_memc_r32(REG_ILL_ACC_ADDR);
	u32 type = rt_memc_r32(REG_ILL_ACC_TYPE);

	dev_err(dev, "illegal %s access from %s - addr:0x%08x offset:%d len:%d\n",
		(type & ILL_ACC_WRITE) ? ("write") : ("read"),
		ill_acc_ids[(type >> ILL_ACC_ID_S) & ILL_ACC_ID_M],
		addr, (type >> ILL_ACC_OFF_S) & ILL_ACC_OFF_M,
		type & ILL_ACC_LEN_M);

	rt_memc_w32(ILL_INT_STATUS, REG_ILL_ACC_TYPE);

	return IRQ_HANDLED;
}