#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_ra_svn_conn_t ;
struct TYPE_7__ {int /*<<< orphan*/  tunnel; } ;
typedef  TYPE_1__ serve_params_t ;
struct TYPE_8__ {int /*<<< orphan*/  remote_host; int /*<<< orphan*/ * authz_user; int /*<<< orphan*/ * user; int /*<<< orphan*/  tunnel_user; int /*<<< orphan*/  tunnel; } ;
typedef  TYPE_2__ client_info_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_2__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_tunnel_user (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_svn_conn_remote_host (int /*<<< orphan*/ *) ; 

client_info_t *
get_client_info(svn_ra_svn_conn_t *conn,
                serve_params_t *params,
                apr_pool_t *pool)
{
  client_info_t *client_info = apr_pcalloc(pool, sizeof(*client_info));

  client_info->tunnel = params->tunnel;
  client_info->tunnel_user = get_tunnel_user(params, pool);
  client_info->user = NULL;
  client_info->authz_user = NULL;
  client_info->remote_host = svn_ra_svn_conn_remote_host(conn);

  return client_info;
}