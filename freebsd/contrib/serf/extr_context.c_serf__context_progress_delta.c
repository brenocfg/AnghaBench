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
struct TYPE_2__ {int /*<<< orphan*/  progress_written; int /*<<< orphan*/  progress_read; int /*<<< orphan*/  progress_baton; int /*<<< orphan*/  (* progress_func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ serf_context_t ;
typedef  scalar_t__ apr_off_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void serf__context_progress_delta(
    void *progress_baton,
    apr_off_t read,
    apr_off_t written)
{
    serf_context_t *ctx = progress_baton;

    ctx->progress_read += read;
    ctx->progress_written += written;

    if (ctx->progress_func)
        ctx->progress_func(ctx->progress_baton,
                           ctx->progress_read,
                           ctx->progress_written);
}