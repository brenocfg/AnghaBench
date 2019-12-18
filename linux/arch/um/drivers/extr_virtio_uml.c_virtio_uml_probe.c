#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct virtio_uml_platform_data {int /*<<< orphan*/  socket_path; int /*<<< orphan*/  virtio_device_id; } ;
struct TYPE_7__ {int /*<<< orphan*/  release; TYPE_4__* parent; } ;
struct TYPE_5__ {int /*<<< orphan*/  vendor; int /*<<< orphan*/  device; } ;
struct TYPE_6__ {TYPE_3__ dev; TYPE_1__ id; int /*<<< orphan*/ * config; } ;
struct virtio_uml_device {int req_fd; int sock; TYPE_2__ vdev; struct platform_device* pdev; } ;
struct TYPE_8__ {struct virtio_uml_platform_data* platform_data; } ;
struct platform_device {TYPE_4__ dev; } ;

/* Variables and functions */
 int EINTR ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  VIRTIO_DEV_ANY_ID ; 
 struct virtio_uml_device* devm_kzalloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_close_file (int) ; 
 int os_connect_socket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct virtio_uml_device*) ; 
 int /*<<< orphan*/  put_device (TYPE_3__*) ; 
 int register_virtio_device (TYPE_2__*) ; 
 int vhost_user_init (struct virtio_uml_device*) ; 
 int /*<<< orphan*/  virtio_uml_config_ops ; 
 int /*<<< orphan*/  virtio_uml_release_dev ; 

__attribute__((used)) static int virtio_uml_probe(struct platform_device *pdev)
{
	struct virtio_uml_platform_data *pdata = pdev->dev.platform_data;
	struct virtio_uml_device *vu_dev;
	int rc;

	if (!pdata)
		return -EINVAL;

	vu_dev = devm_kzalloc(&pdev->dev, sizeof(*vu_dev), GFP_KERNEL);
	if (!vu_dev)
		return -ENOMEM;

	vu_dev->vdev.dev.parent = &pdev->dev;
	vu_dev->vdev.dev.release = virtio_uml_release_dev;
	vu_dev->vdev.config = &virtio_uml_config_ops;
	vu_dev->vdev.id.device = pdata->virtio_device_id;
	vu_dev->vdev.id.vendor = VIRTIO_DEV_ANY_ID;
	vu_dev->pdev = pdev;
	vu_dev->req_fd = -1;

	do {
		rc = os_connect_socket(pdata->socket_path);
	} while (rc == -EINTR);
	if (rc < 0)
		return rc;
	vu_dev->sock = rc;

	rc = vhost_user_init(vu_dev);
	if (rc)
		goto error_init;

	platform_set_drvdata(pdev, vu_dev);

	rc = register_virtio_device(&vu_dev->vdev);
	if (rc)
		put_device(&vu_dev->vdev.dev);
	return rc;

error_init:
	os_close_file(vu_dev->sock);
	return rc;
}