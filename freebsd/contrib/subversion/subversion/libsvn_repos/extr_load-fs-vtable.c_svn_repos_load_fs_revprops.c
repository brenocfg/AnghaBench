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
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_repos_t ;
typedef  int /*<<< orphan*/  svn_repos_parse_fns3_t ;
typedef  int /*<<< orphan*/  svn_repos_notify_func_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_revprop_parser (int /*<<< orphan*/  const**,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_repos_parse_dumpstream3 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_repos_load_fs_revprops(svn_repos_t *repos,
                           svn_stream_t *dumpstream,
                           svn_revnum_t start_rev,
                           svn_revnum_t end_rev,
                           svn_boolean_t validate_props,
                           svn_boolean_t ignore_dates,
                           svn_boolean_t normalize_props,
                           svn_repos_notify_func_t notify_func,
                           void *notify_baton,
                           svn_cancel_func_t cancel_func,
                           void *cancel_baton,
                           apr_pool_t *scratch_pool)
{
  const svn_repos_parse_fns3_t *parser;
  void *parse_baton;

  /* This is really simple. */

  SVN_ERR(build_revprop_parser(&parser, &parse_baton,
                               repos,
                               start_rev, end_rev,
                               validate_props,
                               ignore_dates,
                               normalize_props,
                               notify_func,
                               notify_baton,
                               scratch_pool));

  return svn_repos_parse_dumpstream3(dumpstream, parser, parse_baton, FALSE,
                                     cancel_func, cancel_baton, scratch_pool);
}