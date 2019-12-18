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
struct virtqueue {int /*<<< orphan*/  vdev; } ;
struct TYPE_2__ {int type; } ;
struct virtblk_req {TYPE_1__ status; TYPE_1__ out_hdr; } ;
struct scatterlist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  VIRTIO_BLK_T_OUT ; 
 int cpu_to_virtio32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,TYPE_1__*,int) ; 
 int virtqueue_add_sgs (struct virtqueue*,struct scatterlist**,unsigned int,unsigned int,struct virtblk_req*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int virtblk_add_req(struct virtqueue *vq, struct virtblk_req *vbr,
		struct scatterlist *data_sg, bool have_data)
{
	struct scatterlist hdr, status, *sgs[3];
	unsigned int num_out = 0, num_in = 0;

	sg_init_one(&hdr, &vbr->out_hdr, sizeof(vbr->out_hdr));
	sgs[num_out++] = &hdr;

	if (have_data) {
		if (vbr->out_hdr.type & cpu_to_virtio32(vq->vdev, VIRTIO_BLK_T_OUT))
			sgs[num_out++] = data_sg;
		else
			sgs[num_out + num_in++] = data_sg;
	}

	sg_init_one(&status, &vbr->status, sizeof(vbr->status));
	sgs[num_out + num_in++] = &status;

	return virtqueue_add_sgs(vq, sgs, num_out, num_in, vbr, GFP_ATOMIC);
}