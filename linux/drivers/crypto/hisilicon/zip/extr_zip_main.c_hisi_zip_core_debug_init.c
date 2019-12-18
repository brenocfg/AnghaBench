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
struct hisi_zip_ctrl {int /*<<< orphan*/  debug_root; struct hisi_zip* hisi_zip; } ;
struct hisi_qm {scalar_t__ io_base; TYPE_1__* pdev; } ;
struct hisi_zip {struct hisi_qm qm; } ;
struct device {int dummy; } ;
struct dentry {int dummy; } ;
struct debugfs_regset32 {scalar_t__ base; int /*<<< orphan*/  nregs; int /*<<< orphan*/  regs; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOENT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZIP_BUF_SIZE ; 
 int HZIP_COMP_CORE_NUM ; 
 int HZIP_CORE_NUM ; 
 scalar_t__* core_offsets ; 
 struct dentry* debugfs_create_dir (char*,int /*<<< orphan*/ ) ; 
 struct dentry* debugfs_create_regset32 (char*,int,struct dentry*,struct debugfs_regset32*) ; 
 struct debugfs_regset32* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hzip_dfx_regs ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static int hisi_zip_core_debug_init(struct hisi_zip_ctrl *ctrl)
{
	struct hisi_zip *hisi_zip = ctrl->hisi_zip;
	struct hisi_qm *qm = &hisi_zip->qm;
	struct device *dev = &qm->pdev->dev;
	struct debugfs_regset32 *regset;
	struct dentry *tmp_d, *tmp;
	char buf[HZIP_BUF_SIZE];
	int i;

	for (i = 0; i < HZIP_CORE_NUM; i++) {
		if (i < HZIP_COMP_CORE_NUM)
			sprintf(buf, "comp_core%d", i);
		else
			sprintf(buf, "decomp_core%d", i - HZIP_COMP_CORE_NUM);

		tmp_d = debugfs_create_dir(buf, ctrl->debug_root);
		if (!tmp_d)
			return -ENOENT;

		regset = devm_kzalloc(dev, sizeof(*regset), GFP_KERNEL);
		if (!regset)
			return -ENOENT;

		regset->regs = hzip_dfx_regs;
		regset->nregs = ARRAY_SIZE(hzip_dfx_regs);
		regset->base = qm->io_base + core_offsets[i];

		tmp = debugfs_create_regset32("regs", 0444, tmp_d, regset);
		if (!tmp)
			return -ENOENT;
	}

	return 0;
}