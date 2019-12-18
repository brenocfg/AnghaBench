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
struct virtio_uml_device {int req_fd; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  IRQ_READ ; 
 int /*<<< orphan*/  VHOST_USER_SET_SLAVE_REQ_FD ; 
 int /*<<< orphan*/  VIRTIO_IRQ ; 
 int /*<<< orphan*/  os_close_file (int) ; 
 int os_pipe (int*,int,int) ; 
 int /*<<< orphan*/  um_free_irq (int /*<<< orphan*/ ,struct virtio_uml_device*) ; 
 int um_request_irq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct virtio_uml_device*) ; 
 int vhost_user_send_no_payload_fd (struct virtio_uml_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vu_req_interrupt ; 

__attribute__((used)) static int vhost_user_init_slave_req(struct virtio_uml_device *vu_dev)
{
	int rc, req_fds[2];

	/* Use a pipe for slave req fd, SIGIO is not supported for eventfd */
	rc = os_pipe(req_fds, true, true);
	if (rc < 0)
		return rc;
	vu_dev->req_fd = req_fds[0];

	rc = um_request_irq(VIRTIO_IRQ, vu_dev->req_fd, IRQ_READ,
			    vu_req_interrupt, IRQF_SHARED,
			    vu_dev->pdev->name, vu_dev);
	if (rc)
		goto err_close;

	rc = vhost_user_send_no_payload_fd(vu_dev, VHOST_USER_SET_SLAVE_REQ_FD,
					   req_fds[1]);
	if (rc)
		goto err_free_irq;

	goto out;

err_free_irq:
	um_free_irq(VIRTIO_IRQ, vu_dev);
err_close:
	os_close_file(req_fds[0]);
out:
	/* Close unused write end of request fds */
	os_close_file(req_fds[1]);
	return rc;
}