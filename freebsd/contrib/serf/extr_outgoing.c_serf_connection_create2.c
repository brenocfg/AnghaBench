#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  proxy_address; } ;
typedef  TYPE_1__ serf_context_t ;
struct TYPE_11__ {int /*<<< orphan*/  scheme; void* port; } ;
struct TYPE_13__ {TYPE_10__ host_info; int /*<<< orphan*/  host_url; int /*<<< orphan*/  pool; } ;
typedef  TYPE_2__ serf_connection_t ;
typedef  int /*<<< orphan*/  serf_connection_setup_t ;
typedef  int /*<<< orphan*/  serf_connection_closed_t ;
struct TYPE_14__ {void* port; int /*<<< orphan*/  hostname; int /*<<< orphan*/  scheme; } ;
typedef  TYPE_3__ apr_uri_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_sockaddr_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ APR_SUCCESS ; 
 int /*<<< orphan*/  APR_UNSPEC ; 
 int APR_URI_UNP_OMITPATHINFO ; 
 int APR_URI_UNP_OMITUSERINFO ; 
 scalar_t__ apr_sockaddr_info_get (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_uri_parse (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_10__*) ; 
 void* apr_uri_port_of_scheme (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_uri_unparse (int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 TYPE_2__* serf_connection_create (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

apr_status_t serf_connection_create2(
    serf_connection_t **conn,
    serf_context_t *ctx,
    apr_uri_t host_info,
    serf_connection_setup_t setup,
    void *setup_baton,
    serf_connection_closed_t closed,
    void *closed_baton,
    apr_pool_t *pool)
{
    apr_status_t status = APR_SUCCESS;
    serf_connection_t *c;
    apr_sockaddr_t *host_address = NULL;

    /* Set the port number explicitly, needed to create the socket later. */
    if (!host_info.port) {
        host_info.port = apr_uri_port_of_scheme(host_info.scheme);
    }

    /* Only lookup the address of the server if no proxy server was
       configured. */
    if (!ctx->proxy_address) {
        status = apr_sockaddr_info_get(&host_address,
                                       host_info.hostname,
                                       APR_UNSPEC, host_info.port, 0, pool);
        if (status)
            return status;
    }

    c = serf_connection_create(ctx, host_address, setup, setup_baton,
                               closed, closed_baton, pool);

    /* We're not interested in the path following the hostname. */
    c->host_url = apr_uri_unparse(c->pool,
                                  &host_info,
                                  APR_URI_UNP_OMITPATHINFO |
                                  APR_URI_UNP_OMITUSERINFO);

    /* Store the host info without the path on the connection. */
    (void)apr_uri_parse(c->pool, c->host_url, &(c->host_info));
    if (!c->host_info.port) {
        c->host_info.port = apr_uri_port_of_scheme(c->host_info.scheme);
    }

    *conn = c;

    return status;
}