#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_string_t ;
struct TYPE_11__ {int txn_flags; int /*<<< orphan*/  fs; int /*<<< orphan*/  is_txn_root; } ;
typedef  TYPE_1__ svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_fs_fs__id_part_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_12__ {int /*<<< orphan*/  node; } ;
typedef  TYPE_2__ parent_path_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int apr_int64_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int SVN_FS_TXN_CHECK_LOCKS ; 
 int /*<<< orphan*/ * SVN_FS__NOT_TXN (TYPE_1__*) ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_MERGEINFO ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/ * add_change (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  increment_mergeinfo_up_tree (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  make_path_mutable (TYPE_1__*,TYPE_2__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  open_path (TYPE_2__**,TYPE_1__*,char const*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * root_txn_id (TYPE_1__*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 char* svn_fs__canonicalize_abspath (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__allow_locked_operation (char const*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__dag_get_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_fs__dag_get_proplist (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__dag_has_mergeinfo (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_fs__dag_node_kind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_fs__dag_set_has_mergeinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__dag_set_proplist (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_fs__fs_supports_mergeinfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_path_change_modify ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static svn_error_t *
fs_change_node_prop(svn_fs_root_t *root,
                    const char *path,
                    const char *name,
                    const svn_string_t *value,
                    apr_pool_t *pool)
{
  parent_path_t *parent_path;
  apr_hash_t *proplist;
  const svn_fs_fs__id_part_t *txn_id;
  svn_boolean_t mergeinfo_mod = FALSE;

  if (! root->is_txn_root)
    return SVN_FS__NOT_TXN(root);
  txn_id = root_txn_id(root);

  path = svn_fs__canonicalize_abspath(path, pool);
  SVN_ERR(open_path(&parent_path, root, path, 0, TRUE, pool));

  /* Check (non-recursively) to see if path is locked; if so, check
     that we can use it. */
  if (root->txn_flags & SVN_FS_TXN_CHECK_LOCKS)
    SVN_ERR(svn_fs_fs__allow_locked_operation(path, root->fs, FALSE, FALSE,
                                              pool));

  SVN_ERR(make_path_mutable(root, parent_path, path, pool));
  SVN_ERR(svn_fs_fs__dag_get_proplist(&proplist, parent_path->node, pool));

  /* If there's no proplist, but we're just deleting a property, exit now. */
  if ((! proplist) && (! value))
    return SVN_NO_ERROR;

  /* Now, if there's no proplist, we know we need to make one. */
  if (! proplist)
    proplist = apr_hash_make(pool);

  if (svn_fs_fs__fs_supports_mergeinfo(root->fs)
      && strcmp (name, SVN_PROP_MERGEINFO) == 0)
    {
      apr_int64_t increment = 0;
      svn_boolean_t had_mergeinfo;
      SVN_ERR(svn_fs_fs__dag_has_mergeinfo(&had_mergeinfo, parent_path->node));

      if (value && !had_mergeinfo)
        increment = 1;
      else if (!value && had_mergeinfo)
        increment = -1;

      if (increment != 0)
        {
          SVN_ERR(increment_mergeinfo_up_tree(parent_path, increment, pool));
          SVN_ERR(svn_fs_fs__dag_set_has_mergeinfo(parent_path->node,
                                                   (value != NULL), pool));
        }

      mergeinfo_mod = TRUE;
    }

  /* Set the property. */
  svn_hash_sets(proplist, name, value);

  /* Overwrite the node's proplist. */
  SVN_ERR(svn_fs_fs__dag_set_proplist(parent_path->node, proplist,
                                      pool));

  /* Make a record of this modification in the changes table. */
  return add_change(root->fs, txn_id, path,
                    svn_fs_fs__dag_get_id(parent_path->node),
                    svn_fs_path_change_modify, FALSE, TRUE, mergeinfo_mod,
                    svn_fs_fs__dag_node_kind(parent_path->node),
                    SVN_INVALID_REVNUM, NULL, pool);
}