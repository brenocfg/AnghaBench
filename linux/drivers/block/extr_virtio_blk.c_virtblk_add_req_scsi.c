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
struct virtqueue {int dummy; } ;
struct virtblk_req {int dummy; } ;
struct scatterlist {int dummy; } ;

/* Variables and functions */
 int EIO ; 

__attribute__((used)) static inline int virtblk_add_req_scsi(struct virtqueue *vq,
		struct virtblk_req *vbr, struct scatterlist *data_sg,
		bool have_data)
{
	return -EIO;
}