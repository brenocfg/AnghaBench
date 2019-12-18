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
typedef  int /*<<< orphan*/  serf_request_t ;
typedef  int /*<<< orphan*/  serf_connection_t ;
typedef  int /*<<< orphan*/  serf_bucket_t ;
typedef  int /*<<< orphan*/  serf__authn_scheme_t ;
typedef  int /*<<< orphan*/  peer_t ;
typedef  int /*<<< orphan*/  apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 

__attribute__((used)) static apr_status_t
default_auth_response_handler(const serf__authn_scheme_t *scheme,
                              peer_t peer,
                              int code,
                              serf_connection_t *conn,
                              serf_request_t *request,
                              serf_bucket_t *response,
                              apr_pool_t *pool)
{
    return APR_SUCCESS;
}