#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct fman_rg {TYPE_1__* qmi_rg; TYPE_2__* bmi_rg; } ;
struct fman_cfg {int qmi_def_tnums_thresh; scalar_t__ qmi_deq_option_support; } ;
struct TYPE_4__ {int /*<<< orphan*/  fmbm_init; } ;
struct TYPE_3__ {int /*<<< orphan*/  fmqm_gc; } ;

/* Variables and functions */
 int BMI_INIT_START ; 
 int QMI_CFG_DEQ_EN ; 
 int QMI_CFG_ENQ_EN ; 
 int QMI_CFG_EN_COUNTERS ; 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ *) ; 

int fman_enable(struct fman_rg *fman_rg, struct fman_cfg *cfg)
{
	uint32_t cfg_reg = 0;

	/**********************/
	/* Enable all modules */
	/**********************/
	/* clear & enable global counters  - calculate reg and save for later,
	because it's the same reg for QMI enable */
	cfg_reg = QMI_CFG_EN_COUNTERS;
	if (cfg->qmi_deq_option_support)
		cfg_reg |= (uint32_t)(((cfg->qmi_def_tnums_thresh) << 8) |
				(uint32_t)cfg->qmi_def_tnums_thresh);

	iowrite32be(BMI_INIT_START, &fman_rg->bmi_rg->fmbm_init);
	iowrite32be(cfg_reg | QMI_CFG_ENQ_EN | QMI_CFG_DEQ_EN,
			&fman_rg->qmi_rg->fmqm_gc);

	return 0;
}