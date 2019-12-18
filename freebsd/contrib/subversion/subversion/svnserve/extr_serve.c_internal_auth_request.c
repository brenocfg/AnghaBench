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
struct TYPE_6__ {char* realm; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  auth (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char const*,TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_mechs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_svn__read_tuple (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char const**,char const**) ; 
 int /*<<< orphan*/  svn_ra_svn__write_tuple (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static svn_error_t *
internal_auth_request(svn_ra_svn_conn_t *conn, apr_pool_t *pool,
                      server_baton_t *b, enum access_type required,
                      svn_boolean_t needs_username)
{
  svn_boolean_t success;
  const char *mech, *mecharg;
  apr_pool_t *iterpool;

  SVN_ERR(svn_ra_svn__write_tuple(conn, pool, "w((!", "success"));
  SVN_ERR(send_mechs(conn, pool, b, required, needs_username));
  SVN_ERR(svn_ra_svn__write_tuple(conn, pool, "!)c)", b->repository->realm));

  iterpool = svn_pool_create(pool);
  do
    {
      svn_pool_clear(iterpool);

      SVN_ERR(svn_ra_svn__read_tuple(conn, pool, "w(?c)", &mech, &mecharg));
      if (!*mech)
        break;
      SVN_ERR(auth(&success, conn, mech, mecharg, b, required,
                   needs_username, iterpool));
    }
  while (!success);
  svn_pool_destroy(iterpool);

  return SVN_NO_ERROR;
}