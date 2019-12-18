#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_ra_svn_conn_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_7__ {TYPE_1__* repository; } ;
typedef  TYPE_2__ server_baton_t ;
typedef  enum access_type { ____Placeholder_access_type } access_type ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_6__ {scalar_t__ use_sasl; } ;

/* Variables and functions */
 int /*<<< orphan*/ * cyrus_auth_request (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * internal_auth_request (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *auth_request(svn_ra_svn_conn_t *conn, apr_pool_t *pool,
                                 server_baton_t *b, enum access_type required,
                                 svn_boolean_t needs_username)
{
#ifdef SVN_HAVE_SASL
  if (b->repository->use_sasl)
    return cyrus_auth_request(conn, pool, b, required, needs_username);
#endif

  return internal_auth_request(conn, pool, b, required, needs_username);
}