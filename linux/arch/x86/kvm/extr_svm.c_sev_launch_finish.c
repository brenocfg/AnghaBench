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
struct sev_data_launch_finish {int /*<<< orphan*/  handle; } ;
struct kvm_sev_info {int /*<<< orphan*/  handle; } ;
struct kvm_sev_cmd {int /*<<< orphan*/  error; } ;
struct kvm {int dummy; } ;
struct TYPE_2__ {struct kvm_sev_info sev_info; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOTTY ; 
 int /*<<< orphan*/  GFP_KERNEL_ACCOUNT ; 
 int /*<<< orphan*/  SEV_CMD_LAUNCH_FINISH ; 
 int /*<<< orphan*/  kfree (struct sev_data_launch_finish*) ; 
 struct sev_data_launch_finish* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sev_guest (struct kvm*) ; 
 int sev_issue_cmd (struct kvm*,int /*<<< orphan*/ ,struct sev_data_launch_finish*,int /*<<< orphan*/ *) ; 
 TYPE_1__* to_kvm_svm (struct kvm*) ; 

__attribute__((used)) static int sev_launch_finish(struct kvm *kvm, struct kvm_sev_cmd *argp)
{
	struct kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;
	struct sev_data_launch_finish *data;
	int ret;

	if (!sev_guest(kvm))
		return -ENOTTY;

	data = kzalloc(sizeof(*data), GFP_KERNEL_ACCOUNT);
	if (!data)
		return -ENOMEM;

	data->handle = sev->handle;
	ret = sev_issue_cmd(kvm, SEV_CMD_LAUNCH_FINISH, data, &argp->error);

	kfree(data);
	return ret;
}