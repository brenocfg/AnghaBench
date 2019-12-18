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
typedef  int /*<<< orphan*/  serf_context_t ;
typedef  int /*<<< orphan*/  serf_bucket_t ;
typedef  int /*<<< orphan*/  serf_bucket_alloc_t ;
typedef  int /*<<< orphan*/  apr_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  serf__context_progress_delta ; 
 int /*<<< orphan*/ * serf_bucket_socket_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serf_bucket_socket_set_read_progress_cb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

serf_bucket_t *serf_context_bucket_socket_create(
    serf_context_t *ctx,
    apr_socket_t *skt,
    serf_bucket_alloc_t *allocator)
{
    serf_bucket_t *bucket = serf_bucket_socket_create(skt, allocator);

    /* Use serf's default bytes read/written callback */
    serf_bucket_socket_set_read_progress_cb(bucket,
                                            serf__context_progress_delta,
                                            ctx);

    return bucket;
}