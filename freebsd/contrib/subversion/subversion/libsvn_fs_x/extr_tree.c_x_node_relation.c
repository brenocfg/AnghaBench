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
typedef  int /*<<< orphan*/  svn_fs_x__id_t ;
struct TYPE_5__ {scalar_t__ fs; scalar_t__ is_txn_root; scalar_t__ rev; int /*<<< orphan*/  txn; } ;
typedef  TYPE_1__ svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_fs_node_relation_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int svn_boolean_t ;
typedef  int /*<<< orphan*/  dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_node_common_ancestor ; 
 int /*<<< orphan*/  svn_fs_node_unchanged ; 
 int /*<<< orphan*/  svn_fs_node_unrelated ; 
 int /*<<< orphan*/ * svn_fs_x__dag_get_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_x__dag_get_node_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__get_temp_dag_node (int /*<<< orphan*/ **,TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_x__id_eq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
x_node_relation(svn_fs_node_relation_t *relation,
                svn_fs_root_t *root_a,
                const char *path_a,
                svn_fs_root_t *root_b,
                const char *path_b,
                apr_pool_t *scratch_pool)
{
  dag_node_t *node;
  svn_fs_x__id_t noderev_id_a, noderev_id_b, node_id_a, node_id_b;

  /* Root paths are a common special case. */
  svn_boolean_t a_is_root_dir
    = (path_a[0] == '\0') || ((path_a[0] == '/') && (path_a[1] == '\0'));
  svn_boolean_t b_is_root_dir
    = (path_b[0] == '\0') || ((path_b[0] == '/') && (path_b[1] == '\0'));

  /* Path from different repository are always unrelated. */
  if (root_a->fs != root_b->fs)
    {
      *relation = svn_fs_node_unrelated;
      return SVN_NO_ERROR;
    }

  /* Are both (!) root paths? Then, they are related and we only test how
   * direct the relation is. */
  if (a_is_root_dir && b_is_root_dir)
    {
      svn_boolean_t different_txn
        = root_a->is_txn_root && root_b->is_txn_root
            && strcmp(root_a->txn, root_b->txn);

      /* For txn roots, root->REV is the base revision of that TXN. */
      *relation = (   (root_a->rev == root_b->rev)
                   && (root_a->is_txn_root == root_b->is_txn_root)
                   && !different_txn)
                ? svn_fs_node_unchanged
                : svn_fs_node_common_ancestor;
      return SVN_NO_ERROR;
    }

  /* We checked for all separations between ID spaces (repos, txn).
   * Now, we can simply test for the ID values themselves. */
  SVN_ERR(svn_fs_x__get_temp_dag_node(&node, root_a, path_a, scratch_pool));
  noderev_id_a = *svn_fs_x__dag_get_id(node);
  node_id_a = *svn_fs_x__dag_get_node_id(node);

  SVN_ERR(svn_fs_x__get_temp_dag_node(&node, root_b, path_b, scratch_pool));
  noderev_id_b = *svn_fs_x__dag_get_id(node);
  node_id_b = *svn_fs_x__dag_get_node_id(node);

  /* In FSX, even in-txn IDs are globally unique.
   * So, we can simply compare them. */
  if (svn_fs_x__id_eq(&noderev_id_a, &noderev_id_b))
    *relation = svn_fs_node_unchanged;
  else if (svn_fs_x__id_eq(&node_id_a, &node_id_b))
    *relation = svn_fs_node_common_ancestor;
  else
    *relation = svn_fs_node_unrelated;

  return SVN_NO_ERROR;
}