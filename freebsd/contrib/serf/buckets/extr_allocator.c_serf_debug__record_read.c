#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  track_state_t ;
struct TYPE_8__ {TYPE_1__* allocator; } ;
typedef  TYPE_2__ serf_bucket_t ;
struct TYPE_9__ {int /*<<< orphan*/  last; } ;
typedef  TYPE_3__ read_status_t ;
typedef  int /*<<< orphan*/  apr_status_t ;
struct TYPE_7__ {int /*<<< orphan*/ * track; } ;

/* Variables and functions */
 scalar_t__ APR_STATUS_IS_EAGAIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abort () ; 
 TYPE_3__* find_read_status (int /*<<< orphan*/ *,TYPE_2__ const*,int) ; 

apr_status_t serf_debug__record_read(
    const serf_bucket_t *bucket,
    apr_status_t status)
{
#ifndef SERF_DEBUG_BUCKET_USE
    return status;
#else

    track_state_t *track = bucket->allocator->track;
    read_status_t *rs = find_read_status(track, bucket, 1);

    /* Validate that the previous status value allowed for another read. */
    if (APR_STATUS_IS_EAGAIN(rs->last) /* ### or APR_EOF? */) {
        /* Somebody read when they weren't supposed to. Bail. */
        abort();
    }

    /* Save the current status for later. */
    rs->last = status;

    return status;
#endif
}