#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct iovec {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  allocator; } ;
typedef  TYPE_1__ serf_bucket_t ;

/* Variables and functions */
 int /*<<< orphan*/  serf_bucket_aggregate_append (TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* serf_bucket_iovec_create (struct iovec*,int,int /*<<< orphan*/ ) ; 

void serf_bucket_aggregate_append_iovec(
    serf_bucket_t *aggregate_bucket,
    struct iovec *vecs,
    int vecs_count)
{
    serf_bucket_t *new_bucket;

    new_bucket = serf_bucket_iovec_create(vecs, vecs_count,
                                          aggregate_bucket->allocator);

    serf_bucket_aggregate_append(aggregate_bucket, new_bucket);
}