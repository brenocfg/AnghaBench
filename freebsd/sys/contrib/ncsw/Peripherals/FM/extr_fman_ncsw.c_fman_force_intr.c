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
struct fman_rg {TYPE_1__* bmi_rg; TYPE_2__* qmi_rg; } ;
typedef  enum fman_exceptions { ____Placeholder_fman_exceptions } fman_exceptions ;
struct TYPE_4__ {int /*<<< orphan*/  fmqm_eif; int /*<<< orphan*/  fmqm_if; } ;
struct TYPE_3__ {int /*<<< orphan*/  fmbm_ifr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMI_ERR_INTR_EN_DISPATCH_RAM_ECC ; 
 int /*<<< orphan*/  BMI_ERR_INTR_EN_LIST_RAM_ECC ; 
 int /*<<< orphan*/  BMI_ERR_INTR_EN_STATISTICS_RAM_ECC ; 
 int /*<<< orphan*/  BMI_ERR_INTR_EN_STORAGE_PROFILE_ECC ; 
#define  E_FMAN_EX_BMI_DISPATCH_RAM_ECC 134 
#define  E_FMAN_EX_BMI_LIST_RAM_ECC 133 
#define  E_FMAN_EX_BMI_STATISTICS_RAM_ECC 132 
#define  E_FMAN_EX_BMI_STORAGE_PROFILE_ECC 131 
#define  E_FMAN_EX_QMI_DEQ_FROM_UNKNOWN_PORTID 130 
#define  E_FMAN_EX_QMI_DOUBLE_ECC 129 
#define  E_FMAN_EX_QMI_SINGLE_ECC 128 
 int /*<<< orphan*/  QMI_ERR_INTR_EN_DEQ_FROM_DEF ; 
 int /*<<< orphan*/  QMI_ERR_INTR_EN_DOUBLE_ECC ; 
 int /*<<< orphan*/  QMI_INTR_EN_SINGLE_ECC ; 
 int /*<<< orphan*/  iowrite32be (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void fman_force_intr(struct fman_rg *fman_rg,
		enum fman_exceptions exception)
{
	switch (exception) {
	case E_FMAN_EX_QMI_DEQ_FROM_UNKNOWN_PORTID:
		iowrite32be(QMI_ERR_INTR_EN_DEQ_FROM_DEF,
				&fman_rg->qmi_rg->fmqm_eif);
		break;
	case E_FMAN_EX_QMI_SINGLE_ECC:
		iowrite32be(QMI_INTR_EN_SINGLE_ECC,
				&fman_rg->qmi_rg->fmqm_if);
		break;
	case E_FMAN_EX_QMI_DOUBLE_ECC:
		iowrite32be(QMI_ERR_INTR_EN_DOUBLE_ECC,
				&fman_rg->qmi_rg->fmqm_eif);
		break;
	case E_FMAN_EX_BMI_LIST_RAM_ECC:
		iowrite32be(BMI_ERR_INTR_EN_LIST_RAM_ECC,
				&fman_rg->bmi_rg->fmbm_ifr);
		break;
	case E_FMAN_EX_BMI_STORAGE_PROFILE_ECC:
		iowrite32be(BMI_ERR_INTR_EN_STORAGE_PROFILE_ECC,
				&fman_rg->bmi_rg->fmbm_ifr);
		break;
	case E_FMAN_EX_BMI_STATISTICS_RAM_ECC:
		iowrite32be(BMI_ERR_INTR_EN_STATISTICS_RAM_ECC,
				&fman_rg->bmi_rg->fmbm_ifr);
		break;
	case E_FMAN_EX_BMI_DISPATCH_RAM_ECC:
		iowrite32be(BMI_ERR_INTR_EN_DISPATCH_RAM_ECC,
				&fman_rg->bmi_rg->fmbm_ifr);
		break;
	default:
		break;
	}
}