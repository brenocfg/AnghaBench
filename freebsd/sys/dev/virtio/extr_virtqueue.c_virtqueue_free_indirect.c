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
struct vq_desc_extra {scalar_t__ indirect_paddr; int /*<<< orphan*/ * indirect; } ;
struct virtqueue {int vq_nentries; scalar_t__ vq_indirect_mem_size; int /*<<< orphan*/  vq_flags; struct vq_desc_extra* vq_descx; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  VIRTQUEUE_FLAG_INDIRECT ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
virtqueue_free_indirect(struct virtqueue *vq)
{
	struct vq_desc_extra *dxp;
	int i;

	for (i = 0; i < vq->vq_nentries; i++) {
		dxp = &vq->vq_descx[i];

		if (dxp->indirect == NULL)
			break;

		free(dxp->indirect, M_DEVBUF);
		dxp->indirect = NULL;
		dxp->indirect_paddr = 0;
	}

	vq->vq_flags &= ~VIRTQUEUE_FLAG_INDIRECT;
	vq->vq_indirect_mem_size = 0;
}