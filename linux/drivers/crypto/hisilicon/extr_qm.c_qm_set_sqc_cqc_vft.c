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
typedef  int /*<<< orphan*/  u32 ;
struct hisi_qm {int dummy; } ;

/* Variables and functions */
 int CQC_VFT ; 
 int SQC_VFT ; 
 int qm_set_vft_common (struct hisi_qm*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qm_set_sqc_cqc_vft(struct hisi_qm *qm, u32 fun_num, u32 base,
			      u32 number)
{
	int ret, i;

	for (i = SQC_VFT; i <= CQC_VFT; i++) {
		ret = qm_set_vft_common(qm, i, fun_num, base, number);
		if (ret)
			return ret;
	}

	return 0;
}