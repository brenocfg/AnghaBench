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
struct kvm_device_attr {int group; int /*<<< orphan*/  attr; } ;
struct kvm_device {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  KVMPPC_XIVE_FIRST_IRQ ; 
 int /*<<< orphan*/  KVMPPC_XIVE_NR_IRQS ; 
#define  KVM_DEV_XIVE_EQ_SYNC 134 
#define  KVM_DEV_XIVE_GRP_CTRL 133 
#define  KVM_DEV_XIVE_GRP_EQ_CONFIG 132 
#define  KVM_DEV_XIVE_GRP_SOURCE 131 
#define  KVM_DEV_XIVE_GRP_SOURCE_CONFIG 130 
#define  KVM_DEV_XIVE_GRP_SOURCE_SYNC 129 
#define  KVM_DEV_XIVE_RESET 128 

__attribute__((used)) static int kvmppc_xive_native_has_attr(struct kvm_device *dev,
				       struct kvm_device_attr *attr)
{
	switch (attr->group) {
	case KVM_DEV_XIVE_GRP_CTRL:
		switch (attr->attr) {
		case KVM_DEV_XIVE_RESET:
		case KVM_DEV_XIVE_EQ_SYNC:
			return 0;
		}
		break;
	case KVM_DEV_XIVE_GRP_SOURCE:
	case KVM_DEV_XIVE_GRP_SOURCE_CONFIG:
	case KVM_DEV_XIVE_GRP_SOURCE_SYNC:
		if (attr->attr >= KVMPPC_XIVE_FIRST_IRQ &&
		    attr->attr < KVMPPC_XIVE_NR_IRQS)
			return 0;
		break;
	case KVM_DEV_XIVE_GRP_EQ_CONFIG:
		return 0;
	}
	return -ENXIO;
}