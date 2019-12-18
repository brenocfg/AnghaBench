#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* data; } ;
typedef  TYPE_1__ serf_bucket_t ;
typedef  scalar_t__ (* serf_bucket_headers_do_callback_fn_t ) (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;
struct TYPE_6__ {TYPE_3__* list; } ;
typedef  TYPE_2__ headers_context_t ;
struct TYPE_7__ {struct TYPE_7__* next; int /*<<< orphan*/  value; int /*<<< orphan*/  header; } ;
typedef  TYPE_3__ header_list_t ;

/* Variables and functions */

void serf_bucket_headers_do(
    serf_bucket_t *headers_bucket,
    serf_bucket_headers_do_callback_fn_t func,
    void *baton)
{
    headers_context_t *ctx = headers_bucket->data;
    header_list_t *scan = ctx->list;

    while (scan) {
        if (func(baton, scan->header, scan->value) != 0) {
            break;
        }
        scan = scan->next;
    }
}