#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct kvm_device {TYPE_2__* kvm; } ;
struct TYPE_3__ {struct kvm_device* flic; } ;
struct TYPE_4__ {TYPE_1__ arch; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int flic_create(struct kvm_device *dev, u32 type)
{
	if (!dev)
		return -EINVAL;
	if (dev->kvm->arch.flic)
		return -EINVAL;
	dev->kvm->arch.flic = dev;
	return 0;
}