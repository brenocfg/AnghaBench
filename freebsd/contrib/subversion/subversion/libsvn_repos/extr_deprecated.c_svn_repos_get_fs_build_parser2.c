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
typedef  int /*<<< orphan*/  svn_repos_parse_fns2_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  enum svn_repos_load_uuid { ____Placeholder_svn_repos_load_uuid } svn_repos_load_uuid ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * repos_notify_handler ; 
 int /*<<< orphan*/ * svn_repos_get_fs_build_parser3 (int /*<<< orphan*/  const**,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_repos_get_fs_build_parser2(const svn_repos_parse_fns2_t **parser,
                               void **parse_baton,
                               svn_repos_t *repos,
                               svn_boolean_t use_history,
                               enum svn_repos_load_uuid uuid_action,
                               svn_stream_t *outstream,
                               const char *parent_dir,
                               apr_pool_t *pool)
{
  return svn_repos_get_fs_build_parser3(parser, parse_baton, repos, use_history,
                                        FALSE, uuid_action, parent_dir,
                                        outstream ? repos_notify_handler : NULL,
                                        outstream, pool);
}