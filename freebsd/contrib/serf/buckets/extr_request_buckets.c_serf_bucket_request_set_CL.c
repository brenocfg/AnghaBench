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
struct TYPE_4__ {scalar_t__ data; } ;
typedef  TYPE_1__ serf_bucket_t ;
struct TYPE_5__ {int /*<<< orphan*/  len; } ;
typedef  TYPE_2__ request_context_t ;
typedef  int /*<<< orphan*/  apr_int64_t ;

/* Variables and functions */

void serf_bucket_request_set_CL(
    serf_bucket_t *bucket,
    apr_int64_t len)
{
    request_context_t *ctx = (request_context_t *)bucket->data;

    ctx->len = len;
}