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
typedef  int /*<<< orphan*/  svn_fs_fs__id_part_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct text_baton_t {int /*<<< orphan*/  node; int /*<<< orphan*/  path; TYPE_2__* root; int /*<<< orphan*/  stream; int /*<<< orphan*/  pool; int /*<<< orphan*/  file_stream; } ;
struct TYPE_7__ {int /*<<< orphan*/  node; } ;
typedef  TYPE_1__ parent_path_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_8__ {int txn_flags; int /*<<< orphan*/  fs; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int SVN_FS_TXN_CHECK_LOCKS ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * add_change (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  make_path_mutable (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  open_path (TYPE_1__**,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * root_txn_id (TYPE_2__*) ; 
 int /*<<< orphan*/  svn_fs_fs__allow_locked_operation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__dag_get_edit_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_fs__dag_get_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_path_change_modify ; 
 int /*<<< orphan*/  svn_node_file ; 
 int /*<<< orphan*/  svn_stream_create (struct text_baton_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  text_stream_closer ; 
 int /*<<< orphan*/  text_stream_writer ; 

__attribute__((used)) static svn_error_t *
apply_text(void *baton, apr_pool_t *pool)
{
  struct text_baton_t *tb = baton;
  parent_path_t *parent_path;
  const svn_fs_fs__id_part_t *txn_id = root_txn_id(tb->root);

  /* Call open_path with no flags, as we want this to return an error
     if the node for which we are searching doesn't exist. */
  SVN_ERR(open_path(&parent_path, tb->root, tb->path, 0, TRUE, pool));

  /* Check (non-recursively) to see if path is locked; if so, check
     that we can use it. */
  if (tb->root->txn_flags & SVN_FS_TXN_CHECK_LOCKS)
    SVN_ERR(svn_fs_fs__allow_locked_operation(tb->path, tb->root->fs,
                                              FALSE, FALSE, pool));

  /* Now, make sure this path is mutable. */
  SVN_ERR(make_path_mutable(tb->root, parent_path, tb->path, pool));
  tb->node = parent_path->node;

  /* Make a writable stream for replacing the file's text. */
  SVN_ERR(svn_fs_fs__dag_get_edit_stream(&(tb->file_stream), tb->node,
                                         tb->pool));

  /* Create a 'returnable' stream which writes to the file_stream. */
  tb->stream = svn_stream_create(tb, tb->pool);
  svn_stream_set_write(tb->stream, text_stream_writer);
  svn_stream_set_close(tb->stream, text_stream_closer);

  /* Make a record of this modification in the changes table. */
  return add_change(tb->root->fs, txn_id, tb->path,
                    svn_fs_fs__dag_get_id(tb->node),
                    svn_fs_path_change_modify, TRUE, FALSE, FALSE,
                    svn_node_file, SVN_INVALID_REVNUM, NULL, pool);
}