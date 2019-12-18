#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_fs_x__txn_id_t ;
struct TYPE_9__ {scalar_t__ kind; } ;
typedef  TYPE_1__ svn_fs_x__noderev_t ;
struct TYPE_10__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_2__ svn_fs_x__dirent_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_11__ {int /*<<< orphan*/ * fs; int /*<<< orphan*/  hint; TYPE_1__* node_revision; } ;
typedef  TYPE_3__ dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_NOT_DIRECTORY ; 
 int /*<<< orphan*/  SVN_ERR_FS_NOT_MUTABLE ; 
 int /*<<< orphan*/  SVN_ERR_FS_NOT_SINGLE_PATH_COMPONENT ; 
 int /*<<< orphan*/  SVN_ERR_FS_NO_SUCH_ENTRY ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  delete_if_mutable (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_entry (TYPE_3__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  svn_fs_x__dag_check_mutable (TYPE_3__*) ; 
 int /*<<< orphan*/  svn_fs_x__rep_contents_dir_entry (TYPE_2__**,int /*<<< orphan*/ *,TYPE_1__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 int /*<<< orphan*/  svn_node_unknown ; 
 int /*<<< orphan*/  svn_path_is_single_path_component (char const*) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_x__dag_delete(dag_node_t *parent,
                     const char *name,
                     svn_fs_x__txn_id_t txn_id,
                     apr_pool_t *scratch_pool)
{
  svn_fs_x__noderev_t *parent_noderev = parent->node_revision;
  svn_fs_t *fs = parent->fs;
  svn_fs_x__dirent_t *dirent;
  apr_pool_t *subpool;

  /* Make sure parent is a directory. */
  if (parent_noderev->kind != svn_node_dir)
    return svn_error_createf
      (SVN_ERR_FS_NOT_DIRECTORY, NULL,
       "Attempted to delete entry '%s' from *non*-directory node", name);

  /* Make sure parent is mutable. */
  if (! svn_fs_x__dag_check_mutable(parent))
    return svn_error_createf
      (SVN_ERR_FS_NOT_MUTABLE, NULL,
       "Attempted to delete entry '%s' from immutable directory node", name);

  /* Make sure that NAME is a single path component. */
  if (! svn_path_is_single_path_component(name))
    return svn_error_createf
      (SVN_ERR_FS_NOT_SINGLE_PATH_COMPONENT, NULL,
       "Attempted to delete a node with an illegal name '%s'", name);

  /* We allocate a few potentially heavy temporary objects (file buffers
     and directories).  Make sure we don't keep them around for longer
     than necessary. */
  subpool = svn_pool_create(scratch_pool);

  /* Search this directory for a dirent with that NAME. */
  SVN_ERR(svn_fs_x__rep_contents_dir_entry(&dirent, fs, parent_noderev,
                                           name, &parent->hint,
                                           subpool, subpool));

  /* If we never found ID in ENTRIES (perhaps because there are no
     ENTRIES, perhaps because ID just isn't in the existing ENTRIES
     ... it doesn't matter), return an error.  */
  if (! dirent)
    return svn_error_createf
      (SVN_ERR_FS_NO_SUCH_ENTRY, NULL,
       "Delete failed--directory has no entry '%s'", name);

  /* If mutable, remove it and any mutable children from db. */
  SVN_ERR(delete_if_mutable(parent->fs, &dirent->id, subpool));

  /* Remove this entry from its parent's entries list. */
  SVN_ERR(set_entry(parent, name, NULL, svn_node_unknown, txn_id, subpool));

  svn_pool_destroy(subpool);
  return SVN_NO_ERROR;
}