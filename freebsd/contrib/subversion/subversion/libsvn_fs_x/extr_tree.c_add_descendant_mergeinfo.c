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
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_fs_mergeinfo_receiver_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  crawl_directory_dag_for_mergeinfo (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_x__dag_has_descendants_with_mergeinfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__get_temp_dag_node (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
add_descendant_mergeinfo(svn_fs_root_t *root,
                         const char *path,
                         svn_fs_mergeinfo_receiver_t receiver,
                         void *baton,
                         apr_pool_t *scratch_pool)
{
  dag_node_t *this_dag;

  SVN_ERR(svn_fs_x__get_temp_dag_node(&this_dag, root, path, scratch_pool));
  if (svn_fs_x__dag_has_descendants_with_mergeinfo(this_dag))
    SVN_ERR(crawl_directory_dag_for_mergeinfo(root,
                                              path,
                                              this_dag,
                                              receiver,
                                              baton,
                                              scratch_pool));
  return SVN_NO_ERROR;
}