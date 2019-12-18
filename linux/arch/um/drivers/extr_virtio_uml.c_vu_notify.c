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
typedef  int uint64_t ;
struct virtqueue {struct virtio_uml_vq_info* priv; } ;
struct virtio_uml_vq_info {int /*<<< orphan*/  kick_fd; } ;
typedef  int /*<<< orphan*/  n ;

/* Variables and functions */
 int EINTR ; 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int os_write_file (int /*<<< orphan*/ ,int const*,int) ; 

__attribute__((used)) static bool vu_notify(struct virtqueue *vq)
{
	struct virtio_uml_vq_info *info = vq->priv;
	const uint64_t n = 1;
	int rc;

	do {
		rc = os_write_file(info->kick_fd, &n, sizeof(n));
	} while (rc == -EINTR);
	return !WARN(rc != sizeof(n), "write returned %d\n", rc);
}