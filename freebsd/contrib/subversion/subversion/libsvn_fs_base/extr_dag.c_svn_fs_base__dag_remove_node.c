#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  trail_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_3__ {int /*<<< orphan*/ * predecessor_id; scalar_t__ edit_key; scalar_t__ data_key; scalar_t__ prop_key; } ;
typedef  TYPE_1__ node_revision_t ;
typedef  int /*<<< orphan*/  dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_NOT_MUTABLE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__dag_check_mutable (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_fs_base__dag_get_node (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_base__delete_node_revision (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__delete_rep_if_mutable (int /*<<< orphan*/ *,scalar_t__,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_bdb__get_node_revision (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_base__dag_remove_node(svn_fs_t *fs,
                             const svn_fs_id_t *id,
                             const char *txn_id,
                             trail_t *trail,
                             apr_pool_t *pool)
{
  dag_node_t *node;
  node_revision_t *noderev;

  /* Fetch the node. */
  SVN_ERR(svn_fs_base__dag_get_node(&node, fs, id, trail, pool));

  /* If immutable, do nothing and return immediately. */
  if (! svn_fs_base__dag_check_mutable(node, txn_id))
    return svn_error_createf(SVN_ERR_FS_NOT_MUTABLE, NULL,
                             _("Attempted removal of immutable node"));

  /* Get a fresh node-revision. */
  SVN_ERR(svn_fs_bdb__get_node_revision(&noderev, fs, id, trail, pool));

  /* Delete any mutable property representation. */
  if (noderev->prop_key)
    SVN_ERR(svn_fs_base__delete_rep_if_mutable(fs, noderev->prop_key,
                                               txn_id, trail, pool));

  /* Delete any mutable data representation. */
  if (noderev->data_key)
    SVN_ERR(svn_fs_base__delete_rep_if_mutable(fs, noderev->data_key,
                                               txn_id, trail, pool));

  /* Delete any mutable edit representation (files only). */
  if (noderev->edit_key)
    SVN_ERR(svn_fs_base__delete_rep_if_mutable(fs, noderev->edit_key,
                                               txn_id, trail, pool));

  /* Delete the node revision itself. */
  return svn_fs_base__delete_node_revision(fs, id,
                                           noderev->predecessor_id == NULL,
                                           trail, pool);
}