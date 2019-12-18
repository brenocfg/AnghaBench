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
struct iovec {scalar_t__ iov_len; void* iov_base; } ;
struct TYPE_6__ {TYPE_1__* type; } ;
typedef  TYPE_2__ serf_bucket_t ;
typedef  int /*<<< orphan*/  apr_status_t ;
typedef  scalar_t__ apr_size_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* read ) (TYPE_2__*,scalar_t__,char const**,scalar_t__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*,scalar_t__,char const**,scalar_t__*) ; 

apr_status_t serf_default_read_iovec(
    serf_bucket_t *bucket,
    apr_size_t requested,
    int vecs_size,
    struct iovec *vecs,
    int *vecs_used)
{
    const char *data;
    apr_size_t len;

    /* Read some data from the bucket.
     *
     * Because we're an internal 'helper' to the bucket, we can't call the
     * normal serf_bucket_read() call because the debug allocator tracker will
     * end up marking the bucket as read *twice* - once for us and once for
     * our caller - which is reading the same bucket.  This leads to premature
     * abort()s if we ever see EAGAIN.  Instead, we'll go directly to the
     * vtable and bypass the debug tracker.
     */
    apr_status_t status = bucket->type->read(bucket, requested, &data, &len);

    /* assert that vecs_size >= 1 ? */

    /* Return that data as a single iovec. */
    if (len) {
        vecs[0].iov_base = (void *)data; /* loses the 'const' */
        vecs[0].iov_len = len;
        *vecs_used = 1;
    }
    else {
        *vecs_used = 0;
    }

    return status;
}