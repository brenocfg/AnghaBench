#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ is_txn_root; scalar_t__ fs; scalar_t__ rev; int /*<<< orphan*/  txn; } ;
typedef  TYPE_1__ svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_fs_node_relation_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
struct TYPE_10__ {scalar_t__ revision; } ;
typedef  TYPE_2__ svn_fs_fs__id_part_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int svn_boolean_t ;
typedef  int /*<<< orphan*/  dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  get_dag (int /*<<< orphan*/ **,TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_fs_fs__dag_get_id (int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_fs__id_eq (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 TYPE_2__* svn_fs_fs__id_node_id (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  svn_fs_fs__id_part_eq (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  svn_fs_node_common_ancestor ; 
 int /*<<< orphan*/  svn_fs_node_unchanged ; 
 int /*<<< orphan*/  svn_fs_node_unrelated ; 

__attribute__((used)) static svn_error_t *
fs_node_relation(svn_fs_node_relation_t *relation,
                 svn_fs_root_t *root_a, const char *path_a,
                 svn_fs_root_t *root_b, const char *path_b,
                 apr_pool_t *pool)
{
  dag_node_t *node;
  const svn_fs_id_t *id_a, *id_b;
  svn_fs_fs__id_part_t node_id_a, node_id_b;

  /* Root paths are a common special case. */
  svn_boolean_t a_is_root_dir
    = (path_a[0] == '\0') || ((path_a[0] == '/') && (path_a[1] == '\0'));
  svn_boolean_t b_is_root_dir
    = (path_b[0] == '\0') || ((path_b[0] == '/') && (path_b[1] == '\0'));

  /* Another useful thing to know: Both are txns but not the same txn. */
  svn_boolean_t different_txn
    = root_a->is_txn_root && root_b->is_txn_root
        && strcmp(root_a->txn, root_b->txn);

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
  SVN_ERR(get_dag(&node, root_a, path_a, pool));
  id_a = svn_fs_fs__dag_get_id(node);
  node_id_a = *svn_fs_fs__id_node_id(id_a);

  SVN_ERR(get_dag(&node, root_b, path_b, pool));
  id_b = svn_fs_fs__dag_get_id(node);
  node_id_b = *svn_fs_fs__id_node_id(id_b);

  /* Noderevs from different nodes are unrelated. */
  if (!svn_fs_fs__id_part_eq(&node_id_a, &node_id_b))
    {
      *relation = svn_fs_node_unrelated;
      return SVN_NO_ERROR;
    }

  /* Noderevs have the same node-ID now. So, they *seem* to be related.
   *
   * Special case: Different txns may create the same (txn-local) node ID.
   * These are not related to each other, nor to any other node ID so far. */
  if (different_txn && node_id_a.revision == SVN_INVALID_REVNUM)
    {
      *relation = svn_fs_node_unrelated;
      return SVN_NO_ERROR;
    }

  /* The noderevs are actually related.  Are they the same? */
  if (svn_fs_fs__id_eq(id_a, id_b))
    *relation = svn_fs_node_unchanged;
  else
    *relation = svn_fs_node_common_ancestor;

  return SVN_NO_ERROR;
}