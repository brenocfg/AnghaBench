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
typedef  int /*<<< orphan*/  serf_incoming_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int apr_int16_t ;

/* Variables and functions */
 scalar_t__ APR_ECONNRESET ; 
 scalar_t__ APR_EGENERAL ; 
 int APR_POLLERR ; 
 int APR_POLLHUP ; 
 int APR_POLLIN ; 
 int APR_POLLOUT ; 
 scalar_t__ APR_SUCCESS ; 
 scalar_t__ read_from_client (int /*<<< orphan*/ *) ; 
 scalar_t__ write_to_client (int /*<<< orphan*/ *) ; 

apr_status_t serf__process_client(serf_incoming_t *client, apr_int16_t events)
{
    apr_status_t rv;
    if ((events & APR_POLLIN) != 0) {
        rv = read_from_client(client);
        if (rv) {
            return rv;
        }
    }

    if ((events & APR_POLLHUP) != 0) {
        return APR_ECONNRESET;
    }

    if ((events & APR_POLLERR) != 0) {
        return APR_EGENERAL;
    }

    if ((events & APR_POLLOUT) != 0) {
        rv = write_to_client(client);
        if (rv) {
            return rv;
        }
    }

    return APR_SUCCESS;
}