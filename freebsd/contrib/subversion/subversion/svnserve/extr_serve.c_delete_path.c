#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_ra_svn_conn_t ;
typedef  int /*<<< orphan*/  svn_ra_svn__list_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_2__ {int /*<<< orphan*/  report_baton; scalar_t__ err; } ;
typedef  TYPE_1__ report_driver_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_ra_svn__parse_tuple (int /*<<< orphan*/ *,char*,char const**) ; 
 char* svn_relpath_canonicalize (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_repos_delete_path (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *delete_path(svn_ra_svn_conn_t *conn, apr_pool_t *pool,
                                svn_ra_svn__list_t *params, void *baton)
{
  report_driver_baton_t *b = baton;
  const char *path;

  SVN_ERR(svn_ra_svn__parse_tuple(params, "c", &path));
  path = svn_relpath_canonicalize(path, pool);
  if (!b->err)
    b->err = svn_repos_delete_path(b->report_baton, path, pool);
  return SVN_NO_ERROR;
}