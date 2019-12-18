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
typedef  int /*<<< orphan*/  POOL_ctx ;

/* Variables and functions */

int POOL_resize(POOL_ctx* ctx, size_t numThreads) {
    (void)ctx; (void)numThreads;
    return 0;
}