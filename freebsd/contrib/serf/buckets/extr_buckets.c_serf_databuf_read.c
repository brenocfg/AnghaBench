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
struct TYPE_4__ {scalar_t__ remaining; char* current; scalar_t__ status; } ;
typedef  TYPE_1__ serf_databuf_t ;
typedef  scalar_t__ apr_status_t ;
typedef  scalar_t__ apr_size_t ;

/* Variables and functions */
 scalar_t__ APR_SUCCESS ; 
 scalar_t__ SERF_READ_ALL_AVAIL ; 
 scalar_t__ common_databuf_prep (TYPE_1__*,scalar_t__*) ; 

apr_status_t serf_databuf_read(
    serf_databuf_t *databuf,
    apr_size_t requested,
    const char **data,
    apr_size_t *len)
{
    apr_status_t status = common_databuf_prep(databuf, len);
    if (status)
        return status;

    /* peg the requested amount to what we have remaining */
    if (requested == SERF_READ_ALL_AVAIL || requested > databuf->remaining)
        requested = databuf->remaining;

    /* return the values */
    *data = databuf->current;
    *len = requested;

    /* adjust our internal state to note we've consumed some data */
    databuf->current += requested;
    databuf->remaining -= requested;

    /* If we read everything, then we need to return whatever the data
     * read returned to us. This is going to be APR_EOF or APR_EGAIN.
     * If we have NOT read everything, then return APR_SUCCESS to indicate
     * that we're ready to return some more if asked.
     */
    return databuf->remaining ? APR_SUCCESS : databuf->status;
}