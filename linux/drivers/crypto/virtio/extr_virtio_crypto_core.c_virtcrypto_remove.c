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
struct virtio_device {TYPE_1__* config; int /*<<< orphan*/  dev; struct virtio_crypto* priv; } ;
struct virtio_crypto {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* reset ) (struct virtio_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kfree (struct virtio_crypto*) ; 
 int /*<<< orphan*/  stub1 (struct virtio_device*) ; 
 int /*<<< orphan*/  virtcrypto_clear_crypto_engines (struct virtio_crypto*) ; 
 int /*<<< orphan*/  virtcrypto_del_vqs (struct virtio_crypto*) ; 
 scalar_t__ virtcrypto_dev_started (struct virtio_crypto*) ; 
 int /*<<< orphan*/  virtcrypto_dev_stop (struct virtio_crypto*) ; 
 int /*<<< orphan*/  virtcrypto_devmgr_rm_dev (struct virtio_crypto*) ; 
 int /*<<< orphan*/  virtcrypto_free_unused_reqs (struct virtio_crypto*) ; 

__attribute__((used)) static void virtcrypto_remove(struct virtio_device *vdev)
{
	struct virtio_crypto *vcrypto = vdev->priv;

	dev_info(&vdev->dev, "Start virtcrypto_remove.\n");

	if (virtcrypto_dev_started(vcrypto))
		virtcrypto_dev_stop(vcrypto);
	vdev->config->reset(vdev);
	virtcrypto_free_unused_reqs(vcrypto);
	virtcrypto_clear_crypto_engines(vcrypto);
	virtcrypto_del_vqs(vcrypto);
	virtcrypto_devmgr_rm_dev(vcrypto);
	kfree(vcrypto);
}