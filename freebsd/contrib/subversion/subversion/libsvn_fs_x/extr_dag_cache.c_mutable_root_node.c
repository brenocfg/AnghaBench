#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  rev; int /*<<< orphan*/  fs; int /*<<< orphan*/  is_txn_root; } ;
typedef  TYPE_1__ svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_FS__ERR_NOT_MUTABLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  get_root_node (int /*<<< orphan*/ **,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_x__dag_dup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__root_change_set (TYPE_1__*) ; 

__attribute__((used)) static svn_error_t *
mutable_root_node(dag_node_t **node_p,
                  svn_fs_root_t *root,
                  const char *error_path,
                  apr_pool_t *result_pool,
                  apr_pool_t *scratch_pool)
{
  /* If it's not a transaction root, we can't change its contents.  */
  if (!root->is_txn_root)
    return SVN_FS__ERR_NOT_MUTABLE(root->fs, root->rev, error_path);

  /* It's a transaction root.
     Get the appropriate DAG root node and copy it into RESULT_POOL. */
  SVN_ERR(get_root_node(node_p, root, svn_fs_x__root_change_set(root),
                        scratch_pool));
  *node_p = svn_fs_x__dag_dup(*node_p, result_pool);

  return SVN_NO_ERROR;
}