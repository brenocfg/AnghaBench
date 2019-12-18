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
#define  KVM_DEV_MPIC_BASE_ADDR 131 
#define  KVM_DEV_MPIC_GRP_IRQ_ACTIVE 130 
#define  KVM_DEV_MPIC_GRP_MISC 129 
#define  KVM_DEV_MPIC_GRP_REGISTER 128 
 int /*<<< orphan*/  MAX_SRC ; 

__attribute__((used)) static int mpic_has_attr(struct kvm_device *dev, struct kvm_device_attr *attr)
{
	switch (attr->group) {
	case KVM_DEV_MPIC_GRP_MISC:
		switch (attr->attr) {
		case KVM_DEV_MPIC_BASE_ADDR:
			return 0;
		}

		break;

	case KVM_DEV_MPIC_GRP_REGISTER:
		return 0;

	case KVM_DEV_MPIC_GRP_IRQ_ACTIVE:
		if (attr->attr > MAX_SRC)
			break;

		return 0;
	}

	return -ENXIO;
}