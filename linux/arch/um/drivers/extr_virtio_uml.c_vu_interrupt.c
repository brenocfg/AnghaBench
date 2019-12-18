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
typedef  int /*<<< orphan*/  uint64_t ;
struct virtqueue {struct virtio_uml_vq_info* priv; } ;
struct virtio_uml_vq_info {int /*<<< orphan*/  call_fd; } ;
typedef  int /*<<< orphan*/  n ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int EAGAIN ; 
 int EINTR ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int os_read_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vring_interrupt (int,struct virtqueue*) ; 

__attribute__((used)) static irqreturn_t vu_interrupt(int irq, void *opaque)
{
	struct virtqueue *vq = opaque;
	struct virtio_uml_vq_info *info = vq->priv;
	uint64_t n;
	int rc;
	irqreturn_t ret = IRQ_NONE;

	do {
		rc = os_read_file(info->call_fd, &n, sizeof(n));
		if (rc == sizeof(n))
			ret |= vring_interrupt(irq, vq);
	} while (rc == sizeof(n) || rc == -EINTR);
	WARN(rc != -EAGAIN, "read returned %d\n", rc);
	return ret;
}