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
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
typedef  int /*<<< orphan*/  svn_fs_fs__id_part_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * svn_fs_fs__dag_get_node (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__get_txn_ids (int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__id_eq (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

svn_error_t *
svn_fs_fs__dag_clone_root(dag_node_t **root_p,
                          svn_fs_t *fs,
                          const svn_fs_fs__id_part_t *txn_id,
                          apr_pool_t *pool)
{
  const svn_fs_id_t *base_root_id, *root_id;

  /* Get the node ID's of the root directories of the transaction and
     its base revision.  */
  SVN_ERR(svn_fs_fs__get_txn_ids(&root_id, &base_root_id, fs, txn_id, pool));

  /* Oh, give me a clone...
     (If they're the same, we haven't cloned the transaction's root
     directory yet.)  */
  SVN_ERR_ASSERT(!svn_fs_fs__id_eq(root_id, base_root_id));

  /*
   * (Sung to the tune of "Home, Home on the Range", with thanks to
   * Randall Garrett and Isaac Asimov.)
   */

  /* One way or another, root_id now identifies a cloned root node. */
  return svn_fs_fs__dag_get_node(root_p, fs, root_id, pool);
}