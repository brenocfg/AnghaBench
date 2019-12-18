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
struct sev_data_activate {unsigned int handle; int asid; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL_ACCOUNT ; 
 int /*<<< orphan*/  kfree (struct sev_data_activate*) ; 
 struct sev_data_activate* kzalloc (int,int /*<<< orphan*/ ) ; 
 int sev_get_asid (struct kvm*) ; 
 int sev_guest_activate (struct sev_data_activate*,int*) ; 
 int sev_guest_df_flush (int*) ; 
 int /*<<< orphan*/  wbinvd_on_all_cpus () ; 

__attribute__((used)) static int sev_bind_asid(struct kvm *kvm, unsigned int handle, int *error)
{
	struct sev_data_activate *data;
	int asid = sev_get_asid(kvm);
	int ret;

	wbinvd_on_all_cpus();

	ret = sev_guest_df_flush(error);
	if (ret)
		return ret;

	data = kzalloc(sizeof(*data), GFP_KERNEL_ACCOUNT);
	if (!data)
		return -ENOMEM;

	/* activate ASID on the given handle */
	data->handle = handle;
	data->asid   = asid;
	ret = sev_guest_activate(data, error);
	kfree(data);

	return ret;
}