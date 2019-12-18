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
struct TYPE_3__ {int /*<<< orphan*/  status; scalar_t__ remaining; int /*<<< orphan*/  buf; int /*<<< orphan*/  current; int /*<<< orphan*/  read_baton; int /*<<< orphan*/  (* read ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__*) ;} ;
typedef  TYPE_1__ serf_databuf_t ;
typedef  int /*<<< orphan*/  apr_status_t ;
typedef  scalar_t__ apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_EOF ; 
 scalar_t__ APR_STATUS_IS_EOF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  APR_SUCCESS ; 
 scalar_t__ SERF_BUCKET_READ_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static apr_status_t common_databuf_prep(serf_databuf_t *databuf,
                                        apr_size_t *len)
{
    apr_size_t readlen;
    apr_status_t status;

    /* if there is data in the buffer, then we're happy. */
    if (databuf->remaining > 0)
        return APR_SUCCESS;

    /* if we already hit EOF, then keep returning that. */
    if (APR_STATUS_IS_EOF(databuf->status)) {
        /* *data = NULL;   ?? */
        *len = 0;
        return APR_EOF;
    }

    /* refill the buffer */
    status = (*databuf->read)(databuf->read_baton, sizeof(databuf->buf),
                              databuf->buf, &readlen);
    if (SERF_BUCKET_READ_ERROR(status)) {
        return status;
    }

    databuf->current = databuf->buf;
    databuf->remaining = readlen;
    databuf->status = status;

    return APR_SUCCESS;
}