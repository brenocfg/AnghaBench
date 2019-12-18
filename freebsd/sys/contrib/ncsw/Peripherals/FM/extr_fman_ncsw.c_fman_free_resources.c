#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct fman_rg {TYPE_1__* fpm_rg; TYPE_3__* bmi_rg; TYPE_2__* qmi_rg; } ;
struct TYPE_6__ {int /*<<< orphan*/  fmbm_cfg1; int /*<<< orphan*/  fmbm_cfg2; int /*<<< orphan*/  fmbm_init; } ;
struct TYPE_5__ {int /*<<< orphan*/  fmqm_gc; } ;
struct TYPE_4__ {int /*<<< orphan*/  fm_rcr; } ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite32be (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void fman_free_resources(struct fman_rg *fman_rg)
{
	/* disable BMI and QMI */
	iowrite32be(0, &fman_rg->bmi_rg->fmbm_init);
	iowrite32be(0, &fman_rg->qmi_rg->fmqm_gc);

	/* release BMI resources */
	iowrite32be(0, &fman_rg->bmi_rg->fmbm_cfg2);
	iowrite32be(0, &fman_rg->bmi_rg->fmbm_cfg1);

	/* disable ECC */
	iowrite32be(0, &fman_rg->fpm_rg->fm_rcr);
}