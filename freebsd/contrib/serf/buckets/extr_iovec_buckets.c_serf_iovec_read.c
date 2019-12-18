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
struct iovec {char* iov_base; int /*<<< orphan*/  iov_len; } ;
typedef  int /*<<< orphan*/  serf_bucket_t ;
typedef  int /*<<< orphan*/  apr_status_t ;
typedef  int /*<<< orphan*/  apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  serf_iovec_read_iovec (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,struct iovec*,int*) ; 

__attribute__((used)) static apr_status_t serf_iovec_read(serf_bucket_t *bucket,
                                    apr_size_t requested,
                                    const char **data, apr_size_t *len)
{
    struct iovec vec[1];
    apr_status_t status;
    int vecs_used;

    status = serf_iovec_read_iovec(bucket, requested, 1, vec, &vecs_used);

    if (vecs_used) {
        *data = vec[0].iov_base;
        *len = vec[0].iov_len;
    } else {
        *len = 0;
    }

    return status;
}