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
struct virtio_crypto {int affinity_hint_set; int max_data_queues; TYPE_1__* data_vq; } ;
struct TYPE_2__ {int /*<<< orphan*/  vq; } ;

/* Variables and functions */
 int /*<<< orphan*/  virtqueue_set_affinity (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void virtcrypto_clean_affinity(struct virtio_crypto *vi, long hcpu)
{
	int i;

	if (vi->affinity_hint_set) {
		for (i = 0; i < vi->max_data_queues; i++)
			virtqueue_set_affinity(vi->data_vq[i].vq, NULL);

		vi->affinity_hint_set = false;
	}
}