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
struct sp_device {struct psp_device* psp_data; int /*<<< orphan*/  (* set_psp_master_device ) (struct sp_device*) ;scalar_t__ io_map; TYPE_1__* dev_vdata; struct device* dev; } ;
struct psp_vdata {scalar_t__ inten_reg; scalar_t__ intsts_reg; } ;
struct psp_device {int /*<<< orphan*/  sp; struct psp_vdata* vdata; scalar_t__ io_regs; int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;
struct TYPE_2__ {scalar_t__ psp_vdata; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_notice (struct device*,char*) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 struct psp_device* psp_alloc_struct (struct sp_device*) ; 
 int psp_check_sev_support (struct psp_device*) ; 
 int /*<<< orphan*/  psp_irq_handler ; 
 int sev_misc_init (struct psp_device*) ; 
 int /*<<< orphan*/  sp_free_psp_irq (int /*<<< orphan*/ ,struct psp_device*) ; 
 int sp_request_psp_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct psp_device*) ; 
 int /*<<< orphan*/  stub1 (struct sp_device*) ; 

int psp_dev_init(struct sp_device *sp)
{
	struct device *dev = sp->dev;
	struct psp_device *psp;
	int ret;

	ret = -ENOMEM;
	psp = psp_alloc_struct(sp);
	if (!psp)
		goto e_err;

	sp->psp_data = psp;

	psp->vdata = (struct psp_vdata *)sp->dev_vdata->psp_vdata;
	if (!psp->vdata) {
		ret = -ENODEV;
		dev_err(dev, "missing driver data\n");
		goto e_err;
	}

	psp->io_regs = sp->io_map;

	ret = psp_check_sev_support(psp);
	if (ret)
		goto e_disable;

	/* Disable and clear interrupts until ready */
	iowrite32(0, psp->io_regs + psp->vdata->inten_reg);
	iowrite32(-1, psp->io_regs + psp->vdata->intsts_reg);

	/* Request an irq */
	ret = sp_request_psp_irq(psp->sp, psp_irq_handler, psp->name, psp);
	if (ret) {
		dev_err(dev, "psp: unable to allocate an IRQ\n");
		goto e_err;
	}

	ret = sev_misc_init(psp);
	if (ret)
		goto e_irq;

	if (sp->set_psp_master_device)
		sp->set_psp_master_device(sp);

	/* Enable interrupt */
	iowrite32(-1, psp->io_regs + psp->vdata->inten_reg);

	dev_notice(dev, "psp enabled\n");

	return 0;

e_irq:
	sp_free_psp_irq(psp->sp, psp);
e_err:
	sp->psp_data = NULL;

	dev_notice(dev, "psp initialization failed\n");

	return ret;

e_disable:
	sp->psp_data = NULL;

	return ret;
}