#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  allocator; TYPE_2__* data; } ;
typedef  TYPE_1__ serf_bucket_t ;
struct TYPE_6__ {int /*<<< orphan*/  vecs; } ;
typedef  TYPE_2__ iovec_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  serf_bucket_mem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serf_default_destroy_and_data (TYPE_1__*) ; 

__attribute__((used)) static void serf_iovec_destroy(serf_bucket_t *bucket)
{
    iovec_context_t *ctx = bucket->data;

    serf_bucket_mem_free(bucket->allocator, ctx->vecs);
    serf_default_destroy_and_data(bucket);
}