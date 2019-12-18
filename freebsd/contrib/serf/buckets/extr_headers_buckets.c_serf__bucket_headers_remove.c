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
struct TYPE_6__ {TYPE_3__* last; TYPE_3__* list; } ;
typedef  TYPE_2__ headers_context_t ;
struct TYPE_7__ {struct TYPE_7__* next; int /*<<< orphan*/  header; } ;
typedef  TYPE_3__ header_list_t ;

/* Variables and functions */
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char const*) ; 

void serf__bucket_headers_remove(serf_bucket_t *bucket, const char *header)
{
    headers_context_t *ctx = bucket->data;
    header_list_t *scan = ctx->list, *prev = NULL;

    /* Find and delete all items with the same header (case insensitive) */
    while (scan) {
        if (strcasecmp(scan->header, header) == 0) {
            if (prev) {
                prev->next = scan->next;
            } else {
                ctx->list = scan->next;
            }
            if (ctx->last == scan) {
                ctx->last = NULL;
            }
        } else {
            prev = scan;
        }
        scan = scan->next;
    }
}