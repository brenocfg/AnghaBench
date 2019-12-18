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
struct TYPE_2__ {int /*<<< orphan*/  loop; int /*<<< orphan*/  should_exit; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT32_MAX ; 
 int /*<<< orphan*/  UV_RUN_ONCE ; 
 int /*<<< orphan*/  h2o_evloop_run (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_run (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ worker_thread ; 

__attribute__((used)) static void *worker_main(void *_unused)
{
    while (!worker_thread.should_exit) {
#if H2O_USE_LIBUV
        uv_run(worker_thread.loop, UV_RUN_ONCE);
#else
        h2o_evloop_run(worker_thread.loop, INT32_MAX);
#endif
    }

    return NULL;
}