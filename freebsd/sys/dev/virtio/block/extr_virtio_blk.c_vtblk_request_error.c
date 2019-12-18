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
struct vtblk_request {int vbr_ack; } ;

/* Variables and functions */
 int EIO ; 
 int ENOTSUP ; 
#define  VIRTIO_BLK_S_OK 129 
#define  VIRTIO_BLK_S_UNSUPP 128 

__attribute__((used)) static int
vtblk_request_error(struct vtblk_request *req)
{
	int error;

	switch (req->vbr_ack) {
	case VIRTIO_BLK_S_OK:
		error = 0;
		break;
	case VIRTIO_BLK_S_UNSUPP:
		error = ENOTSUP;
		break;
	default:
		error = EIO;
		break;
	}

	return (error);
}