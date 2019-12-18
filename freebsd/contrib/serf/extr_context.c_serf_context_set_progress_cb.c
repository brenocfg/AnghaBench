#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  serf_progress_t ;
struct TYPE_3__ {void* progress_baton; int /*<<< orphan*/  progress_func; } ;
typedef  TYPE_1__ serf_context_t ;

/* Variables and functions */

void serf_context_set_progress_cb(
    serf_context_t *ctx,
    const serf_progress_t progress_func,
    void *progress_baton)
{
    ctx->progress_func = progress_func;
    ctx->progress_baton = progress_baton;
}