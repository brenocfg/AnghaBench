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
struct hisi_qm {int qp_num; int ctrl_qp_num; } ;
struct hisi_zip {struct hisi_qm qm; } ;

/* Variables and functions */
 int EINVAL ; 
 int hisi_qm_set_vft (struct hisi_qm*,int,int,int) ; 

__attribute__((used)) static int hisi_zip_vf_q_assign(struct hisi_zip *hisi_zip, int num_vfs)
{
	struct hisi_qm *qm = &hisi_zip->qm;
	u32 qp_num = qm->qp_num;
	u32 q_base = qp_num;
	u32 q_num, remain_q_num, i;
	int ret;

	if (!num_vfs)
		return -EINVAL;

	remain_q_num = qm->ctrl_qp_num - qp_num;
	if (remain_q_num < num_vfs)
		return -EINVAL;

	q_num = remain_q_num / num_vfs;
	for (i = 1; i <= num_vfs; i++) {
		if (i == num_vfs)
			q_num += remain_q_num % num_vfs;
		ret = hisi_qm_set_vft(qm, i, q_base, q_num);
		if (ret)
			return ret;
		q_base += q_num;
	}

	return 0;
}