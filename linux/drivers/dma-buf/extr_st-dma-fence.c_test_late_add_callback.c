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
struct simple_cb {scalar_t__ seen; int /*<<< orphan*/  cb; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  dma_fence_add_callback (struct dma_fence*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_fence_signal (struct dma_fence*) ; 
 struct dma_fence* mock_fence () ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  simple_callback ; 

__attribute__((used)) static int test_late_add_callback(void *arg)
{
	struct simple_cb cb = {};
	struct dma_fence *f;
	int err = -EINVAL;

	f = mock_fence();
	if (!f)
		return -ENOMEM;

	dma_fence_signal(f);

	if (!dma_fence_add_callback(f, &cb.cb, simple_callback)) {
		pr_err("Added callback, but fence was already signaled!\n");
		goto err_free;
	}

	dma_fence_signal(f);
	if (cb.seen) {
		pr_err("Callback called after failed attachment !\n");
		goto err_free;
	}

	err = 0;
err_free:
	dma_fence_put(f);
	return err;
}