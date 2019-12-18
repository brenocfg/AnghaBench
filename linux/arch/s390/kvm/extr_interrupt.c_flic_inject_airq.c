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
struct s390_io_adapter {int dummy; } ;
struct kvm_device_attr {unsigned int attr; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct s390_io_adapter* get_io_adapter (struct kvm*,unsigned int) ; 
 int kvm_s390_inject_airq (struct kvm*,struct s390_io_adapter*) ; 

__attribute__((used)) static int flic_inject_airq(struct kvm *kvm, struct kvm_device_attr *attr)
{
	unsigned int id = attr->attr;
	struct s390_io_adapter *adapter = get_io_adapter(kvm, id);

	if (!adapter)
		return -EINVAL;

	return kvm_s390_inject_airq(kvm, adapter);
}