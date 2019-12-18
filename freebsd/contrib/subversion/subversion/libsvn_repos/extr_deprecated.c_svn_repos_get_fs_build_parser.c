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
typedef  int /*<<< orphan*/  svn_repos_t ;
typedef  int /*<<< orphan*/  svn_repos_parser_fns_t ;
typedef  int /*<<< orphan*/  svn_repos_parse_fns2_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  enum svn_repos_load_uuid { ____Placeholder_svn_repos_load_uuid } svn_repos_load_uuid ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * fns_from_fns2 (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos_get_fs_build_parser2 (int /*<<< orphan*/  const**,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_repos_get_fs_build_parser(const svn_repos_parser_fns_t **parser_callbacks,
                              void **parse_baton,
                              svn_repos_t *repos,
                              svn_boolean_t use_history,
                              enum svn_repos_load_uuid uuid_action,
                              svn_stream_t *outstream,
                              const char *parent_dir,
                              apr_pool_t *pool)
{
  const svn_repos_parse_fns2_t *fns2;

  SVN_ERR(svn_repos_get_fs_build_parser2(&fns2, parse_baton, repos,
                                         use_history, uuid_action, outstream,
                                         parent_dir, pool));

  *parser_callbacks = fns_from_fns2(fns2, pool);
  return SVN_NO_ERROR;
}