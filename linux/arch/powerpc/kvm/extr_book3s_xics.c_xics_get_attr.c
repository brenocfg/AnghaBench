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
struct kvmppc_xics {int dummy; } ;
struct kvm_device_attr {int group; int /*<<< orphan*/  addr; int /*<<< orphan*/  attr; } ;
struct kvm_device {struct kvmppc_xics* private; } ;

/* Variables and functions */
 int ENXIO ; 
#define  KVM_DEV_XICS_GRP_SOURCES 128 
 int xics_get_source (struct kvmppc_xics*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xics_get_attr(struct kvm_device *dev, struct kvm_device_attr *attr)
{
	struct kvmppc_xics *xics = dev->private;

	switch (attr->group) {
	case KVM_DEV_XICS_GRP_SOURCES:
		return xics_get_source(xics, attr->attr, attr->addr);
	}
	return -ENXIO;
}