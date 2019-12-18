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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct hisi_qm {scalar_t__ io_base; int /*<<< orphan*/  ver; } ;
typedef  enum vft_type { ____Placeholder_vft_type } vft_type ;

/* Variables and functions */
#define  CQC_VFT 132 
 int QM_CQC_VFT_BUF_SIZE ; 
 int QM_CQC_VFT_INDEX_NUMBER ; 
 int QM_CQC_VFT_SQC_SIZE ; 
 int QM_CQC_VFT_VALID ; 
#define  QM_HW_UNKNOWN 131 
#define  QM_HW_V1 130 
#define  QM_HW_V2 129 
 int QM_SQC_VFT_BUF_SIZE ; 
 int QM_SQC_VFT_INDEX_NUMBER ; 
 int QM_SQC_VFT_SQC_SIZE ; 
 int QM_SQC_VFT_SQN_SHIFT ; 
 int QM_SQC_VFT_START_SQN_SHIFT ; 
 int QM_SQC_VFT_VALID ; 
 scalar_t__ QM_VFT_CFG_DATA_H ; 
 scalar_t__ QM_VFT_CFG_DATA_L ; 
#define  SQC_VFT 128 
 int /*<<< orphan*/  lower_32_bits (int) ; 
 int /*<<< orphan*/  upper_32_bits (int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void qm_vft_data_cfg(struct hisi_qm *qm, enum vft_type type, u32 base,
			    u32 number)
{
	u64 tmp = 0;

	if (number > 0) {
		switch (type) {
		case SQC_VFT:
			switch (qm->ver) {
			case QM_HW_V1:
				tmp = QM_SQC_VFT_BUF_SIZE	|
				      QM_SQC_VFT_SQC_SIZE	|
				      QM_SQC_VFT_INDEX_NUMBER	|
				      QM_SQC_VFT_VALID		|
				      (u64)base << QM_SQC_VFT_START_SQN_SHIFT;
				break;
			case QM_HW_V2:
				tmp = (u64)base << QM_SQC_VFT_START_SQN_SHIFT |
				      QM_SQC_VFT_VALID |
				      (u64)(number - 1) << QM_SQC_VFT_SQN_SHIFT;
				break;
			case QM_HW_UNKNOWN:
				break;
			}
			break;
		case CQC_VFT:
			switch (qm->ver) {
			case QM_HW_V1:
				tmp = QM_CQC_VFT_BUF_SIZE	|
				      QM_CQC_VFT_SQC_SIZE	|
				      QM_CQC_VFT_INDEX_NUMBER	|
				      QM_CQC_VFT_VALID;
				break;
			case QM_HW_V2:
				tmp = QM_CQC_VFT_VALID;
				break;
			case QM_HW_UNKNOWN:
				break;
			}
			break;
		}
	}

	writel(lower_32_bits(tmp), qm->io_base + QM_VFT_CFG_DATA_L);
	writel(upper_32_bits(tmp), qm->io_base + QM_VFT_CFG_DATA_H);
}