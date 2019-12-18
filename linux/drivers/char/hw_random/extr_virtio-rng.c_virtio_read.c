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
struct virtrng_info {int busy; int data_avail; int /*<<< orphan*/  have_data; scalar_t__ hwrng_removed; } ;
struct hwrng {scalar_t__ priv; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  register_buffer (struct virtrng_info*,void*,size_t) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int wait_for_completion_killable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int virtio_read(struct hwrng *rng, void *buf, size_t size, bool wait)
{
	int ret;
	struct virtrng_info *vi = (struct virtrng_info *)rng->priv;

	if (vi->hwrng_removed)
		return -ENODEV;

	if (!vi->busy) {
		vi->busy = true;
		reinit_completion(&vi->have_data);
		register_buffer(vi, buf, size);
	}

	if (!wait)
		return 0;

	ret = wait_for_completion_killable(&vi->have_data);
	if (ret < 0)
		return ret;

	vi->busy = false;

	return vi->data_avail;
}