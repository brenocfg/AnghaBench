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
struct dma_fence {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct dma_fence**) ; 
 int EINVAL ; 
 struct dma_fence* dma_fence_get_stub () ; 
 int /*<<< orphan*/  dma_fence_is_signaled (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int test_stub(void *arg)
{
	struct dma_fence *f[64];
	int err = -EINVAL;
	int i;

	for (i = 0; i < ARRAY_SIZE(f); i++) {
		f[i] = dma_fence_get_stub();
		if (!dma_fence_is_signaled(f[i])) {
			pr_err("Obtained unsignaled stub fence!\n");
			goto err;
		}
	}

	err = 0;
err:
	while (i--)
		dma_fence_put(f[i]);
	return err;
}