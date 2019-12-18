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
struct virtqueue {int vq_nentries; TYPE_1__* vq_descx; } ;
struct TYPE_2__ {int /*<<< orphan*/ * cookie; } ;

/* Variables and functions */
 int /*<<< orphan*/  vq_ring_free_chain (struct virtqueue*,int) ; 

void *
virtqueue_drain(struct virtqueue *vq, int *last)
{
	void *cookie;
	int idx;

	cookie = NULL;
	idx = *last;

	while (idx < vq->vq_nentries && cookie == NULL) {
		if ((cookie = vq->vq_descx[idx].cookie) != NULL) {
			vq->vq_descx[idx].cookie = NULL;
			/* Free chain to keep free count consistent. */
			vq_ring_free_chain(vq, idx);
		}
		idx++;
	}

	*last = idx;

	return (cookie);
}