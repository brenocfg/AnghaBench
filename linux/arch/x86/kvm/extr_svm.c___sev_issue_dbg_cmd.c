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
struct sev_data_dbg {unsigned long dst_addr; unsigned long src_addr; int len; int /*<<< orphan*/  handle; } ;
struct kvm_sev_info {int /*<<< orphan*/  handle; } ;
struct kvm {int dummy; } ;
struct TYPE_2__ {struct kvm_sev_info sev_info; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL_ACCOUNT ; 
 int /*<<< orphan*/  SEV_CMD_DBG_DECRYPT ; 
 int /*<<< orphan*/  SEV_CMD_DBG_ENCRYPT ; 
 int /*<<< orphan*/  kfree (struct sev_data_dbg*) ; 
 struct sev_data_dbg* kzalloc (int,int /*<<< orphan*/ ) ; 
 int sev_issue_cmd (struct kvm*,int /*<<< orphan*/ ,struct sev_data_dbg*,int*) ; 
 TYPE_1__* to_kvm_svm (struct kvm*) ; 

__attribute__((used)) static int __sev_issue_dbg_cmd(struct kvm *kvm, unsigned long src,
			       unsigned long dst, int size,
			       int *error, bool enc)
{
	struct kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;
	struct sev_data_dbg *data;
	int ret;

	data = kzalloc(sizeof(*data), GFP_KERNEL_ACCOUNT);
	if (!data)
		return -ENOMEM;

	data->handle = sev->handle;
	data->dst_addr = dst;
	data->src_addr = src;
	data->len = size;

	ret = sev_issue_cmd(kvm,
			    enc ? SEV_CMD_DBG_ENCRYPT : SEV_CMD_DBG_DECRYPT,
			    data, error);
	kfree(data);
	return ret;
}