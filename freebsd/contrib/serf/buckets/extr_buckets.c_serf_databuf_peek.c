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
struct TYPE_4__ {char* current; int /*<<< orphan*/  status; int /*<<< orphan*/  remaining; } ;
typedef  TYPE_1__ serf_databuf_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_size_t ;

/* Variables and functions */
 scalar_t__ APR_EOF ; 
 scalar_t__ APR_STATUS_IS_EOF (int /*<<< orphan*/ ) ; 
 scalar_t__ APR_SUCCESS ; 
 scalar_t__ common_databuf_prep (TYPE_1__*,int /*<<< orphan*/ *) ; 

apr_status_t serf_databuf_peek(
    serf_databuf_t *databuf,
    const char **data,
    apr_size_t *len)
{
    apr_status_t status = common_databuf_prep(databuf, len);
    if (status)
        return status;

    /* return everything we have */
    *data = databuf->current;
    *len = databuf->remaining;

    /* If the last read returned EOF, then the peek should return the same.
     * The other possibility in databuf->status is APR_EAGAIN, which we
     * should never return. Thus, just return APR_SUCCESS for non-EOF cases.
     */
    if (APR_STATUS_IS_EOF(databuf->status))
        return APR_EOF;
    return APR_SUCCESS;
}