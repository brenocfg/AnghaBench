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
struct hisi_zip_ctrl {int num_vfs; } ;
struct hisi_qm {int dummy; } ;
struct hisi_zip {struct hisi_qm qm; struct hisi_zip_ctrl* ctrl; } ;

/* Variables and functions */
 int hisi_qm_set_vft (struct hisi_qm*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hisi_zip_clear_vft_config(struct hisi_zip *hisi_zip)
{
	struct hisi_zip_ctrl *ctrl = hisi_zip->ctrl;
	struct hisi_qm *qm = &hisi_zip->qm;
	u32 i, num_vfs = ctrl->num_vfs;
	int ret;

	for (i = 1; i <= num_vfs; i++) {
		ret = hisi_qm_set_vft(qm, i, 0, 0);
		if (ret)
			return ret;
	}

	ctrl->num_vfs = 0;

	return 0;
}