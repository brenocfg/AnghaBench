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
typedef  int /*<<< orphan*/  IjkThreadPoolContext ;

/* Variables and functions */
 int ijk_threadpool_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ijk_threadpool_freep(IjkThreadPoolContext **ctx)
{
    int ret = 0;

    if (!ctx || !*ctx)
        return -1;

    ret = ijk_threadpool_free(*ctx);
    *ctx = NULL;
    return ret;
}