#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  serf_bucket_type_t ;
struct TYPE_9__ {int /*<<< orphan*/  const* type; TYPE_3__* data; } ;
typedef  TYPE_2__ serf_bucket_t ;
struct TYPE_10__ {TYPE_1__* list; } ;
typedef  TYPE_3__ aggregate_context_t ;
struct TYPE_8__ {TYPE_2__* bucket; struct TYPE_8__* next; } ;

/* Variables and functions */
 TYPE_2__* serf_bucket_read_bucket (TYPE_2__*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static serf_bucket_t * serf_aggregate_read_bucket(
    serf_bucket_t *bucket,
    const serf_bucket_type_t *type)
{
    aggregate_context_t *ctx = bucket->data;
    serf_bucket_t *found_bucket;

    if (!ctx->list) {
        return NULL;
    }

    if (ctx->list->bucket->type == type) {
        /* Got the bucket. Consume it from our list. */
        found_bucket = ctx->list->bucket;
        ctx->list = ctx->list->next;
        return found_bucket;
    }

    /* Call read_bucket on first one in our list. */
    return serf_bucket_read_bucket(ctx->list->bucket, type);
}