#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  serf_bucket_t ;
typedef  int /*<<< orphan*/  serf_bucket_alloc_t ;
typedef  int /*<<< orphan*/  aggregate_context_t ;

/* Variables and functions */
 int /*<<< orphan*/ * create_aggregate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * serf_bucket_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serf_bucket_type_aggregate ; 

serf_bucket_t *serf_bucket_aggregate_create(
    serf_bucket_alloc_t *allocator)
{
    aggregate_context_t *ctx;

    ctx = create_aggregate(allocator);

    return serf_bucket_create(&serf_bucket_type_aggregate, allocator, ctx);
}