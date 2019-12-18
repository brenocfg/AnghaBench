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
struct TYPE_2__ {int /*<<< orphan*/  debug_root; } ;
struct hisi_qm {scalar_t__ fun_type; TYPE_1__ debug; } ;
struct hisi_zip {struct hisi_qm qm; } ;

/* Variables and functions */
 scalar_t__ QM_HW_PF ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_zip_debug_regs_clear (struct hisi_zip*) ; 

__attribute__((used)) static void hisi_zip_debugfs_exit(struct hisi_zip *hisi_zip)
{
	struct hisi_qm *qm = &hisi_zip->qm;

	debugfs_remove_recursive(qm->debug.debug_root);

	if (qm->fun_type == QM_HW_PF)
		hisi_zip_debug_regs_clear(hisi_zip);
}