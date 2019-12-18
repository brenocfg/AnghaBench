#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* progress_baton; int /*<<< orphan*/  progress_func; } ;
typedef  TYPE_1__ socket_context_t ;
typedef  int /*<<< orphan*/  serf_progress_t ;
struct TYPE_5__ {TYPE_1__* data; } ;
typedef  TYPE_2__ serf_bucket_t ;

/* Variables and functions */

void serf_bucket_socket_set_read_progress_cb(
    serf_bucket_t *bucket,
    const serf_progress_t progress_func,
    void *progress_baton)
{
    socket_context_t *ctx = bucket->data;

    ctx->progress_func = progress_func;
    ctx->progress_baton = progress_baton;
}