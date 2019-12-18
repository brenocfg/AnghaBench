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
struct kvm_pic {int /*<<< orphan*/  dev_master; int /*<<< orphan*/  dev_slave; int /*<<< orphan*/  dev_eclr; TYPE_1__* pics; struct kvm* kvm; int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {struct kvm_pic* vpic; } ;
struct kvm {int /*<<< orphan*/  slots_lock; TYPE_2__ arch; } ;
struct TYPE_3__ {int elcr_mask; struct kvm_pic* pics_state; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL_ACCOUNT ; 
 int /*<<< orphan*/  KVM_PIO_BUS ; 
 int /*<<< orphan*/  kfree (struct kvm_pic*) ; 
 int kvm_io_bus_register_dev (struct kvm*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_io_bus_unregister_dev (struct kvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_iodevice_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct kvm_pic* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  picdev_eclr_ops ; 
 int /*<<< orphan*/  picdev_master_ops ; 
 int /*<<< orphan*/  picdev_slave_ops ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int kvm_pic_init(struct kvm *kvm)
{
	struct kvm_pic *s;
	int ret;

	s = kzalloc(sizeof(struct kvm_pic), GFP_KERNEL_ACCOUNT);
	if (!s)
		return -ENOMEM;
	spin_lock_init(&s->lock);
	s->kvm = kvm;
	s->pics[0].elcr_mask = 0xf8;
	s->pics[1].elcr_mask = 0xde;
	s->pics[0].pics_state = s;
	s->pics[1].pics_state = s;

	/*
	 * Initialize PIO device
	 */
	kvm_iodevice_init(&s->dev_master, &picdev_master_ops);
	kvm_iodevice_init(&s->dev_slave, &picdev_slave_ops);
	kvm_iodevice_init(&s->dev_eclr, &picdev_eclr_ops);
	mutex_lock(&kvm->slots_lock);
	ret = kvm_io_bus_register_dev(kvm, KVM_PIO_BUS, 0x20, 2,
				      &s->dev_master);
	if (ret < 0)
		goto fail_unlock;

	ret = kvm_io_bus_register_dev(kvm, KVM_PIO_BUS, 0xa0, 2, &s->dev_slave);
	if (ret < 0)
		goto fail_unreg_2;

	ret = kvm_io_bus_register_dev(kvm, KVM_PIO_BUS, 0x4d0, 2, &s->dev_eclr);
	if (ret < 0)
		goto fail_unreg_1;

	mutex_unlock(&kvm->slots_lock);

	kvm->arch.vpic = s;

	return 0;

fail_unreg_1:
	kvm_io_bus_unregister_dev(kvm, KVM_PIO_BUS, &s->dev_slave);

fail_unreg_2:
	kvm_io_bus_unregister_dev(kvm, KVM_PIO_BUS, &s->dev_master);

fail_unlock:
	mutex_unlock(&kvm->slots_lock);

	kfree(s);

	return ret;
}