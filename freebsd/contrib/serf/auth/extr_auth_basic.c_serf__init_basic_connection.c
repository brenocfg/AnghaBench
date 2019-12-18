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
struct TYPE_9__ {scalar_t__ baton; } ;
struct TYPE_7__ {TYPE_3__ proxy_authn_info; } ;
typedef  TYPE_1__ serf_context_t ;
struct TYPE_8__ {TYPE_1__* ctx; } ;
typedef  TYPE_2__ serf_connection_t ;
typedef  int /*<<< orphan*/  serf__authn_scheme_t ;
typedef  TYPE_3__ serf__authn_info_t ;
typedef  int /*<<< orphan*/  basic_authn_info_t ;
typedef  int /*<<< orphan*/  apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 
 scalar_t__ apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 TYPE_3__* serf__get_authn_info_for_server (TYPE_2__*) ; 

apr_status_t
serf__init_basic_connection(const serf__authn_scheme_t *scheme,
                            int code,
                            serf_connection_t *conn,
                            apr_pool_t *pool)
{
    serf_context_t *ctx = conn->ctx;
    serf__authn_info_t *authn_info;

    if (code == 401) {
        authn_info = serf__get_authn_info_for_server(conn);
    } else {
        authn_info = &ctx->proxy_authn_info;
    }

    if (!authn_info->baton) {
        authn_info->baton = apr_pcalloc(pool, sizeof(basic_authn_info_t));
    }

    return APR_SUCCESS;
}