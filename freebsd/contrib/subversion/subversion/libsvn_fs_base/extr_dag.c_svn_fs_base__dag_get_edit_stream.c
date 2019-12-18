#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  trail_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_7__ {char const* edit_key; } ;
typedef  TYPE_1__ node_revision_t ;
struct TYPE_8__ {scalar_t__ kind; int /*<<< orphan*/  id; int /*<<< orphan*/ * fs; } ;
typedef  TYPE_2__ dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_NOT_FILE ; 
 int /*<<< orphan*/  SVN_ERR_FS_NOT_MUTABLE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__dag_check_mutable (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  svn_fs_base__delete_rep_if_mutable (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__get_mutable_rep (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__rep_contents_write_stream (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_bdb__get_node_revision (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_bdb__put_node_revision (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_file ; 

svn_error_t *
svn_fs_base__dag_get_edit_stream(svn_stream_t **contents,
                                 dag_node_t *file,
                                 const char *txn_id,
                                 trail_t *trail,
                                 apr_pool_t *pool)
{
  svn_fs_t *fs = file->fs;   /* just for nicer indentation */
  node_revision_t *noderev;
  const char *mutable_rep_key;
  svn_stream_t *ws;

  /* Make sure our node is a file. */
  if (file->kind != svn_node_file)
    return svn_error_createf
      (SVN_ERR_FS_NOT_FILE, NULL,
       _("Attempted to set textual contents of a *non*-file node"));

  /* Make sure our node is mutable. */
  if (! svn_fs_base__dag_check_mutable(file, txn_id))
    return svn_error_createf
      (SVN_ERR_FS_NOT_MUTABLE, NULL,
       _("Attempted to set textual contents of an immutable node"));

  /* Get the node revision. */
  SVN_ERR(svn_fs_bdb__get_node_revision(&noderev, fs, file->id,
                                        trail, pool));

  /* If this node already has an EDIT-DATA-KEY, destroy the data
     associated with that key.  */
  if (noderev->edit_key)
    SVN_ERR(svn_fs_base__delete_rep_if_mutable(fs, noderev->edit_key,
                                               txn_id, trail, pool));

  /* Now, let's ensure that we have a new EDIT-DATA-KEY available for
     use. */
  SVN_ERR(svn_fs_base__get_mutable_rep(&mutable_rep_key, NULL, fs,
                                       txn_id, trail, pool));

  /* We made a new rep, so update the node revision. */
  noderev->edit_key = mutable_rep_key;
  SVN_ERR(svn_fs_bdb__put_node_revision(fs, file->id, noderev,
                                        trail, pool));

  /* Return a writable stream with which to set new contents. */
  SVN_ERR(svn_fs_base__rep_contents_write_stream(&ws, fs, mutable_rep_key,
                                                 txn_id, FALSE, trail,
                                                 pool));
  *contents = ws;

  return SVN_NO_ERROR;
}