#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  track_state_t ;
struct TYPE_12__ {TYPE_1__* allocator; } ;
typedef  TYPE_2__ serf_bucket_t ;
struct TYPE_13__ {scalar_t__ last; } ;
typedef  TYPE_3__ read_status_t ;
struct TYPE_11__ {int /*<<< orphan*/ * track; } ;

/* Variables and functions */
 scalar_t__ APR_EOF ; 
 scalar_t__ SERF_BUCKET_IS_BARRIER (TYPE_2__ const*) ; 
 scalar_t__ SERF_BUCKET_IS_SOCKET (TYPE_2__ const*) ; 
 scalar_t__ SERF_BUCKET_IS_SSL_DECRYPT (TYPE_2__ const*) ; 
 scalar_t__ SERF_BUCKET_IS_SSL_ENCRYPT (TYPE_2__ const*) ; 
 int /*<<< orphan*/  abort () ; 
 TYPE_3__* find_read_status (int /*<<< orphan*/ *,TYPE_2__ const*,int /*<<< orphan*/ ) ; 

void serf_debug__bucket_destroy(const serf_bucket_t *bucket)
{
#ifdef SERF_DEBUG_BUCKET_USE

    track_state_t *track = bucket->allocator->track;
    read_status_t *rs = find_read_status(track, bucket, 0);

    if (rs != NULL && rs->last != APR_EOF) {
        /* The bucket was destroyed before it was read to completion. */

        /* Special exception for socket buckets. If a connection remains
         * open, they are not read to completion.
         */
        if (SERF_BUCKET_IS_SOCKET(bucket))
            return;

        /* Ditto for SSL Decrypt buckets. */
        if (SERF_BUCKET_IS_SSL_DECRYPT(bucket))
            return;

        /* Ditto for SSL Encrypt buckets. */
        if (SERF_BUCKET_IS_SSL_ENCRYPT(bucket))
            return;

        /* Ditto for barrier buckets. */
        if (SERF_BUCKET_IS_BARRIER(bucket))
            return;


        abort();
    }

#endif
}