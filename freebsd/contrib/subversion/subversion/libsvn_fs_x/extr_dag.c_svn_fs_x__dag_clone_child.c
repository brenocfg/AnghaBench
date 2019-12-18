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
typedef  int /*<<< orphan*/  svn_fs_x__txn_id_t ;
struct TYPE_13__ {int /*<<< orphan*/  kind; int /*<<< orphan*/  noderev_id; int /*<<< orphan*/  copy_id; int /*<<< orphan*/  created_path; int /*<<< orphan*/  predecessor_count; int /*<<< orphan*/  predecessor_id; int /*<<< orphan*/  copyfrom_rev; int /*<<< orphan*/ * copyfrom_path; int /*<<< orphan*/  copyroot_path; int /*<<< orphan*/  copyroot_rev; } ;
typedef  TYPE_1__ svn_fs_x__noderev_t ;
typedef  int /*<<< orphan*/  svn_fs_x__id_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_14__ {TYPE_1__* node_revision; } ;
typedef  TYPE_2__ dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_NOT_FOUND ; 
 int /*<<< orphan*/  SVN_ERR_FS_NOT_MUTABLE ; 
 int /*<<< orphan*/  SVN_ERR_FS_NOT_SINGLE_PATH_COMPONENT ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_entry (TYPE_2__*,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  svn_fs_x__create_successor (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_x__dag_check_mutable (TYPE_2__*) ; 
 int /*<<< orphan*/ * svn_fs_x__dag_get_fs (TYPE_2__*) ; 
 int /*<<< orphan*/ * svn_fs_x__dag_get_id (TYPE_2__*) ; 
 int /*<<< orphan*/ * svn_fs_x__dag_get_node (TYPE_2__**,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__dag_open (TYPE_2__**,TYPE_2__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fspath__join (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_path_is_single_path_component (char const*) ; 

svn_error_t *
svn_fs_x__dag_clone_child(dag_node_t **child_p,
                          dag_node_t *parent,
                          const char *parent_path,
                          const char *name,
                          const svn_fs_x__id_t *copy_id,
                          svn_fs_x__txn_id_t txn_id,
                          svn_boolean_t is_parent_copyroot,
                          apr_pool_t *result_pool,
                          apr_pool_t *scratch_pool)
{
  dag_node_t *cur_entry; /* parent's current entry named NAME */
  const svn_fs_x__id_t *new_node_id; /* node id we'll put into NEW_NODE */
  svn_fs_t *fs = svn_fs_x__dag_get_fs(parent);

  /* First check that the parent is mutable. */
  if (! svn_fs_x__dag_check_mutable(parent))
    return svn_error_createf
      (SVN_ERR_FS_NOT_MUTABLE, NULL,
       "Attempted to clone child of non-mutable node");

  /* Make sure that NAME is a single path component. */
  if (! svn_path_is_single_path_component(name))
    return svn_error_createf
      (SVN_ERR_FS_NOT_SINGLE_PATH_COMPONENT, NULL,
       "Attempted to make a child clone with an illegal name '%s'", name);

  /* Find the node named NAME in PARENT's entries list if it exists. */
  SVN_ERR(svn_fs_x__dag_open(&cur_entry, parent, name, scratch_pool,
                             scratch_pool));
  if (! cur_entry)
    return svn_error_createf
      (SVN_ERR_FS_NOT_FOUND, NULL,
       "Attempted to open non-existent child node '%s'", name);

  /* Check for mutability in the node we found.  If it's mutable, we
     don't need to clone it. */
  if (svn_fs_x__dag_check_mutable(cur_entry))
    {
      /* This has already been cloned */
      new_node_id = svn_fs_x__dag_get_id(cur_entry);
    }
  else
    {
      svn_fs_x__noderev_t *noderev = cur_entry->node_revision;

      if (is_parent_copyroot)
        {
          svn_fs_x__noderev_t *parent_noderev = parent->node_revision;
          noderev->copyroot_rev = parent_noderev->copyroot_rev;
          noderev->copyroot_path = apr_pstrdup(scratch_pool,
                                               parent_noderev->copyroot_path);
        }

      noderev->copyfrom_path = NULL;
      noderev->copyfrom_rev = SVN_INVALID_REVNUM;

      noderev->predecessor_id = noderev->noderev_id;
      noderev->predecessor_count++;
      noderev->created_path = svn_fspath__join(parent_path, name,
                                               scratch_pool);

      if (copy_id == NULL)
        copy_id = &noderev->copy_id;

      SVN_ERR(svn_fs_x__create_successor(fs, noderev, copy_id, txn_id,
                                         scratch_pool));
      new_node_id = &noderev->noderev_id;

      /* Replace the ID in the parent's ENTRY list with the ID which
         refers to the mutable clone of this child. */
      SVN_ERR(set_entry(parent, name, new_node_id, noderev->kind, txn_id,
                        scratch_pool));
    }

  /* Initialize the youngster. */
  return svn_fs_x__dag_get_node(child_p, fs, new_node_id, result_pool,
                                scratch_pool);
}