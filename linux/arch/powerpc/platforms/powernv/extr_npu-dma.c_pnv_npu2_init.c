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
struct pci_controller {struct npu* npu; } ;
struct npu {int index; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NV_MAX_NPUS ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (struct npu*) ; 
 struct npu* kzalloc (int,int /*<<< orphan*/ ) ; 

int pnv_npu2_init(struct pci_controller *hose)
{
	static int npu_index;
	struct npu *npu;
	int ret;

	npu = kzalloc(sizeof(*npu), GFP_KERNEL);
	if (!npu)
		return -ENOMEM;

	npu_index++;
	if (WARN_ON(npu_index >= NV_MAX_NPUS)) {
		ret = -ENOSPC;
		goto fail_exit;
	}
	npu->index = npu_index;
	hose->npu = npu;

	return 0;

fail_exit:
	kfree(npu);
	return ret;
}