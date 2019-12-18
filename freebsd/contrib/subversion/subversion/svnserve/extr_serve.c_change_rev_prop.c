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
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_svn_conn_t ;
typedef  int /*<<< orphan*/  svn_ra_svn__list_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  server_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  do_change_rev_prop (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_svn__parse_tuple (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ **) ; 

__attribute__((used)) static svn_error_t *
change_rev_prop(svn_ra_svn_conn_t *conn,
                apr_pool_t *pool,
                svn_ra_svn__list_t *params,
                void *baton)
{
  server_baton_t *b = baton;
  svn_revnum_t rev;
  const char *name;
  svn_string_t *value;

  /* Because the revprop value was at one time mandatory, the usual
     optional element pattern "(?s)" isn't used. */
  SVN_ERR(svn_ra_svn__parse_tuple(params, "rc?s", &rev, &name, &value));

  SVN_ERR(do_change_rev_prop(conn, b, rev, name, NULL, value, pool));

  return SVN_NO_ERROR;
}