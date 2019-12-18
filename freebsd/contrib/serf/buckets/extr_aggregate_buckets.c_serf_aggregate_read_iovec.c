#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct iovec {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  allocator; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ serf_bucket_t ;
typedef  int /*<<< orphan*/  apr_status_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  aggregate_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  cleanup_aggregate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_aggregate (TYPE_1__*,int /*<<< orphan*/ ,int,struct iovec*,int*) ; 

__attribute__((used)) static apr_status_t serf_aggregate_read_iovec(serf_bucket_t *bucket,
                                              apr_size_t requested,
                                              int vecs_size,
                                              struct iovec *vecs,
                                              int *vecs_used)
{
    aggregate_context_t *ctx = bucket->data;

    cleanup_aggregate(ctx, bucket->allocator);

    return read_aggregate(bucket, requested, vecs_size, vecs, vecs_used);
}