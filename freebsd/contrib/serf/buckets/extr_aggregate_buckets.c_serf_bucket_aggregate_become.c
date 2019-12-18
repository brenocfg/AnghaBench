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
struct TYPE_3__ {int /*<<< orphan*/ * data; int /*<<< orphan*/ * type; int /*<<< orphan*/  allocator; } ;
typedef  TYPE_1__ serf_bucket_t ;
typedef  int /*<<< orphan*/  aggregate_context_t ;

/* Variables and functions */
 int /*<<< orphan*/ * create_aggregate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serf_bucket_type_aggregate ; 

void serf_bucket_aggregate_become(serf_bucket_t *bucket)
{
    aggregate_context_t *ctx;

    ctx = create_aggregate(bucket->allocator);

    bucket->type = &serf_bucket_type_aggregate;
    bucket->data = ctx;

    /* The allocator remains the same. */
}