#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  path; TYPE_4__* root; int /*<<< orphan*/  stream; int /*<<< orphan*/  pool; int /*<<< orphan*/  node; int /*<<< orphan*/  file_stream; } ;
typedef  TYPE_1__ text_baton_t ;
typedef  int /*<<< orphan*/  svn_fs_x__txn_id_t ;
struct TYPE_10__ {int /*<<< orphan*/  node; } ;
typedef  TYPE_2__ svn_fs_x__dag_path_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_11__ {int txn_flags; int /*<<< orphan*/  fs; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int SVN_FS_TXN_CHECK_LOCKS ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * add_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_path_change_modify ; 
 int /*<<< orphan*/  svn_fs_x__allow_locked_operation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__dag_dup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__dag_get_edit_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__get_dag_path (TYPE_2__**,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__make_path_mutable (TYPE_4__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__root_txn_id (TYPE_4__*) ; 
 int /*<<< orphan*/  svn_node_file ; 
 int /*<<< orphan*/  svn_stream_create (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  text_stream_closer ; 
 int /*<<< orphan*/  text_stream_writer ; 

__attribute__((used)) static svn_error_t *
apply_text(void *baton,
           apr_pool_t *scratch_pool)
{
  text_baton_t *tb = baton;
  svn_fs_x__dag_path_t *dag_path;
  svn_fs_x__txn_id_t txn_id = svn_fs_x__root_txn_id(tb->root);

  /* Call open_path with no flags, as we want this to return an error
     if the node for which we are searching doesn't exist. */
  SVN_ERR(svn_fs_x__get_dag_path(&dag_path, tb->root, tb->path, 0, TRUE,
                                 scratch_pool, scratch_pool));

  /* Check (non-recursively) to see if path is locked; if so, check
     that we can use it. */
  if (tb->root->txn_flags & SVN_FS_TXN_CHECK_LOCKS)
    SVN_ERR(svn_fs_x__allow_locked_operation(tb->path, tb->root->fs,
                                             FALSE, FALSE, scratch_pool));

  /* Now, make sure this path is mutable. */
  SVN_ERR(svn_fs_x__make_path_mutable(tb->root, dag_path, tb->path,
                                      scratch_pool, scratch_pool));
  tb->node = svn_fs_x__dag_dup(dag_path->node, tb->pool);

  /* Make a writable stream for replacing the file's text. */
  SVN_ERR(svn_fs_x__dag_get_edit_stream(&(tb->file_stream), tb->node,
                                        tb->pool));

  /* Create a 'returnable' stream which writes to the file_stream. */
  tb->stream = svn_stream_create(tb, tb->pool);
  svn_stream_set_write(tb->stream, text_stream_writer);
  svn_stream_set_close(tb->stream, text_stream_closer);

  /* Make a record of this modification in the changes table. */
  return add_change(tb->root->fs, txn_id, tb->path,
                    svn_fs_path_change_modify, TRUE, FALSE, FALSE,
                    svn_node_file, SVN_INVALID_REVNUM, NULL, scratch_pool);
}