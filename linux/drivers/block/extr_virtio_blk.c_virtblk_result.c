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
struct virtblk_req {int status; } ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  BLK_STS_NOTSUPP ; 
 int /*<<< orphan*/  BLK_STS_OK ; 
#define  VIRTIO_BLK_S_OK 129 
#define  VIRTIO_BLK_S_UNSUPP 128 

__attribute__((used)) static inline blk_status_t virtblk_result(struct virtblk_req *vbr)
{
	switch (vbr->status) {
	case VIRTIO_BLK_S_OK:
		return BLK_STS_OK;
	case VIRTIO_BLK_S_UNSUPP:
		return BLK_STS_NOTSUPP;
	default:
		return BLK_STS_IOERR;
	}
}