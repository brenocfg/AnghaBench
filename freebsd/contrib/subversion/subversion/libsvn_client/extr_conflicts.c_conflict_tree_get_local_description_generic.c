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
typedef  int svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
typedef  int /*<<< orphan*/  svn_client_conflict_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  describe_local_dir_node_change (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  describe_local_file_node_change (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  describe_local_none_node_change (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int svn_client_conflict_tree_get_victim_node_kind (int /*<<< orphan*/ *) ; 
#define  svn_node_dir 132 
#define  svn_node_file 131 
#define  svn_node_none 130 
#define  svn_node_symlink 129 
#define  svn_node_unknown 128 

__attribute__((used)) static svn_error_t *
conflict_tree_get_local_description_generic(const char **description,
                                            svn_client_conflict_t *conflict,
                                            svn_client_ctx_t *ctx,
                                            apr_pool_t *result_pool,
                                            apr_pool_t *scratch_pool)
{
  svn_node_kind_t victim_node_kind;

  victim_node_kind = svn_client_conflict_tree_get_victim_node_kind(conflict);

  *description = NULL;

  switch (victim_node_kind)
    {
      case svn_node_file:
      case svn_node_symlink:
        SVN_ERR(describe_local_file_node_change(description, conflict, ctx,
                                                result_pool, scratch_pool));
        break;
      case svn_node_dir:
        SVN_ERR(describe_local_dir_node_change(description, conflict, ctx,
                                               result_pool, scratch_pool));
        break;
      case svn_node_none:
      case svn_node_unknown:
        SVN_ERR(describe_local_none_node_change(description, conflict,
                                                result_pool, scratch_pool));
        break;
    }

  return SVN_NO_ERROR;
}