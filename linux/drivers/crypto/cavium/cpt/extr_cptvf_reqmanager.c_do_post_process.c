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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct cpt_vf {struct pci_dev* pdev; } ;
struct cpt_info_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  do_request_cleanup (struct cpt_vf*,struct cpt_info_buffer*) ; 

__attribute__((used)) static void do_post_process(struct cpt_vf *cptvf, struct cpt_info_buffer *info)
{
	struct pci_dev *pdev = cptvf->pdev;

	if (!info) {
		dev_err(&pdev->dev, "incorrect cpt_info_buffer for post processing\n");
		return;
	}

	do_request_cleanup(cptvf, info);
}