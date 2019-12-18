#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  trail_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_13__ {int predecessor_count; int /*<<< orphan*/  created_path; int /*<<< orphan*/ * predecessor_id; } ;
typedef  TYPE_1__ node_revision_t ;
struct TYPE_14__ {int /*<<< orphan*/ * id; } ;
typedef  TYPE_2__ dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_NOT_MUTABLE ; 
 int /*<<< orphan*/  SVN_ERR_FS_NOT_SINGLE_PATH_COMPONENT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  set_entry (TYPE_2__*,char const*,int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  svn_fs_base__create_successor (int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_base__dag_check_mutable (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/ * svn_fs_base__dag_get_fs (TYPE_2__*) ; 
 int /*<<< orphan*/ * svn_fs_base__dag_get_node (TYPE_2__**,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__dag_open (TYPE_2__**,TYPE_2__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_bdb__get_node_revision (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fspath__join (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_path_is_single_path_component (char const*) ; 

svn_error_t *
svn_fs_base__dag_clone_child(dag_node_t **child_p,
                             dag_node_t *parent,
                             const char *parent_path,
                             const char *name,
                             const char *copy_id,
                             const char *txn_id,
                             trail_t *trail,
                             apr_pool_t *pool)
{
  dag_node_t *cur_entry; /* parent's current entry named NAME */
  const svn_fs_id_t *new_node_id; /* node id we'll put into NEW_NODE */
  svn_fs_t *fs = svn_fs_base__dag_get_fs(parent);

  /* First check that the parent is mutable. */
  if (! svn_fs_base__dag_check_mutable(parent, txn_id))
    return svn_error_createf
      (SVN_ERR_FS_NOT_MUTABLE, NULL,
       _("Attempted to clone child of non-mutable node"));

  /* Make sure that NAME is a single path component. */
  if (! svn_path_is_single_path_component(name))
    return svn_error_createf
      (SVN_ERR_FS_NOT_SINGLE_PATH_COMPONENT, NULL,
       _("Attempted to make a child clone with an illegal name '%s'"), name);

  /* Find the node named NAME in PARENT's entries list if it exists. */
  SVN_ERR(svn_fs_base__dag_open(&cur_entry, parent, name, trail, pool));

  /* Check for mutability in the node we found.  If it's mutable, we
     don't need to clone it. */
  if (svn_fs_base__dag_check_mutable(cur_entry, txn_id))
    {
      /* This has already been cloned */
      new_node_id = cur_entry->id;
    }
  else
    {
      node_revision_t *noderev;

      /* Go get a fresh NODE-REVISION for current child node. */
      SVN_ERR(svn_fs_bdb__get_node_revision(&noderev, fs, cur_entry->id,
                                            trail, pool));

      /* Do the clone thingy here. */
      noderev->predecessor_id = cur_entry->id;
      if (noderev->predecessor_count != -1)
        noderev->predecessor_count++;
      noderev->created_path = svn_fspath__join(parent_path, name, pool);
      SVN_ERR(svn_fs_base__create_successor(&new_node_id, fs, cur_entry->id,
                                            noderev, copy_id, txn_id,
                                            trail, pool));

      /* Replace the ID in the parent's ENTRY list with the ID which
         refers to the mutable clone of this child. */
      SVN_ERR(set_entry(parent, name, new_node_id, txn_id, trail, pool));
    }

  /* Initialize the youngster. */
  return svn_fs_base__dag_get_node(child_p, fs, new_node_id, trail, pool);
}