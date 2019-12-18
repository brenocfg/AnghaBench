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
typedef  int /*<<< orphan*/  svn_fs_x__txn_id_t ;
struct TYPE_11__ {scalar_t__ kind; int /*<<< orphan*/  noderev_id; int /*<<< orphan*/  copy_id; int /*<<< orphan*/  predecessor_id; int /*<<< orphan*/ * copyfrom_path; int /*<<< orphan*/  copyfrom_rev; int /*<<< orphan*/  copyroot_rev; int /*<<< orphan*/  copyroot_path; int /*<<< orphan*/  created_path; } ;
typedef  TYPE_1__ svn_fs_x__noderev_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  new_noderev ;
struct TYPE_12__ {TYPE_1__* node_revision; } ;
typedef  TYPE_2__ dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_NOT_DIRECTORY ; 
 int /*<<< orphan*/  SVN_ERR_FS_NOT_MUTABLE ; 
 int /*<<< orphan*/  SVN_ERR_FS_NOT_SINGLE_PATH_COMPONENT ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * set_entry (TYPE_2__*,char const*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  svn_fs_x__create_node (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__dag_check_mutable (TYPE_2__*) ; 
 int /*<<< orphan*/  svn_fs_x__dag_get_fs (TYPE_2__*) ; 
 int /*<<< orphan*/  svn_fs_x__dag_get_node (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__id_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fspath__join (char const*,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 int /*<<< orphan*/  svn_path_is_single_path_component (char const*) ; 

__attribute__((used)) static svn_error_t *
make_entry(dag_node_t **child_p,
           dag_node_t *parent,
           const char *parent_path,
           const char *name,
           svn_boolean_t is_dir,
           svn_fs_x__txn_id_t txn_id,
           apr_pool_t *result_pool,
           apr_pool_t *scratch_pool)
{
  svn_fs_x__noderev_t new_noderev;
  svn_fs_x__noderev_t *parent_noderev = parent->node_revision;

  /* Make sure that NAME is a single path component. */
  if (! svn_path_is_single_path_component(name))
    return svn_error_createf
      (SVN_ERR_FS_NOT_SINGLE_PATH_COMPONENT, NULL,
       _("Attempted to create a node with an illegal name '%s'"), name);

  /* Make sure that parent is a directory */
  if (parent_noderev->kind != svn_node_dir)
    return svn_error_create
      (SVN_ERR_FS_NOT_DIRECTORY, NULL,
       _("Attempted to create entry in non-directory parent"));

  /* Check that the parent is mutable. */
  if (! svn_fs_x__dag_check_mutable(parent))
    return svn_error_createf
      (SVN_ERR_FS_NOT_MUTABLE, NULL,
       _("Attempted to clone child of non-mutable node"));

  /* Create the new node's NODE-REVISION */
  memset(&new_noderev, 0, sizeof(new_noderev));
  new_noderev.kind = is_dir ? svn_node_dir : svn_node_file;
  new_noderev.created_path = svn_fspath__join(parent_path, name, result_pool);

  new_noderev.copyroot_path = apr_pstrdup(result_pool,
                                          parent_noderev->copyroot_path);
  new_noderev.copyroot_rev = parent_noderev->copyroot_rev;
  new_noderev.copyfrom_rev = SVN_INVALID_REVNUM;
  new_noderev.copyfrom_path = NULL;
  svn_fs_x__id_reset(&new_noderev.predecessor_id);

  SVN_ERR(svn_fs_x__create_node
          (svn_fs_x__dag_get_fs(parent), &new_noderev,
           &parent_noderev->copy_id, txn_id, scratch_pool));

  /* Create a new dag_node_t for our new node */
  SVN_ERR(svn_fs_x__dag_get_node(child_p, svn_fs_x__dag_get_fs(parent),
                                 &new_noderev.noderev_id, result_pool,
                                 scratch_pool));

  /* We can safely call set_entry because we already know that
     PARENT is mutable, and we just created CHILD, so we know it has
     no ancestors (therefore, PARENT cannot be an ancestor of CHILD) */
  return set_entry(parent, name, &new_noderev.noderev_id,
                   new_noderev.kind, txn_id, scratch_pool);
}