#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct fw_cdev_add_descriptor {int length; int /*<<< orphan*/  handle; int /*<<< orphan*/  key; int /*<<< orphan*/  immediate; int /*<<< orphan*/  data; } ;
union ioctl_arg {struct fw_cdev_add_descriptor add_descriptor; } ;
struct TYPE_7__ {int /*<<< orphan*/  handle; int /*<<< orphan*/  release; } ;
struct TYPE_6__ {int length; int /*<<< orphan*/  data; int /*<<< orphan*/  key; int /*<<< orphan*/  immediate; } ;
struct descriptor_resource {TYPE_4__ resource; TYPE_2__ descriptor; int /*<<< orphan*/  data; } ;
struct client {TYPE_1__* device; } ;
struct TYPE_5__ {int /*<<< orphan*/  is_local; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENOSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int add_client_resource (struct client*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ copy_from_user (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int fw_core_add_descriptor (TYPE_2__*) ; 
 int /*<<< orphan*/  fw_core_remove_descriptor (TYPE_2__*) ; 
 int /*<<< orphan*/  kfree (struct descriptor_resource*) ; 
 struct descriptor_resource* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_descriptor ; 
 int /*<<< orphan*/  u64_to_uptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ioctl_add_descriptor(struct client *client, union ioctl_arg *arg)
{
	struct fw_cdev_add_descriptor *a = &arg->add_descriptor;
	struct descriptor_resource *r;
	int ret;

	/* Access policy: Allow this ioctl only on local nodes' device files. */
	if (!client->device->is_local)
		return -ENOSYS;

	if (a->length > 256)
		return -EINVAL;

	r = kmalloc(sizeof(*r) + a->length * 4, GFP_KERNEL);
	if (r == NULL)
		return -ENOMEM;

	if (copy_from_user(r->data, u64_to_uptr(a->data), a->length * 4)) {
		ret = -EFAULT;
		goto failed;
	}

	r->descriptor.length    = a->length;
	r->descriptor.immediate = a->immediate;
	r->descriptor.key       = a->key;
	r->descriptor.data      = r->data;

	ret = fw_core_add_descriptor(&r->descriptor);
	if (ret < 0)
		goto failed;

	r->resource.release = release_descriptor;
	ret = add_client_resource(client, &r->resource, GFP_KERNEL);
	if (ret < 0) {
		fw_core_remove_descriptor(&r->descriptor);
		goto failed;
	}
	a->handle = r->resource.handle;

	return 0;
 failed:
	kfree(r);

	return ret;
}