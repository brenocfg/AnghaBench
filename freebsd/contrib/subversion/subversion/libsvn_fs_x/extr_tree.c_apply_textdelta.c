#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  path; TYPE_3__* root; int /*<<< orphan*/  interpreter_baton; int /*<<< orphan*/  interpreter; int /*<<< orphan*/  pool; int /*<<< orphan*/  target_stream; int /*<<< orphan*/  source_stream; int /*<<< orphan*/  node; TYPE_8__* base_checksum; } ;
typedef  TYPE_1__ txdelta_baton_t ;
typedef  int /*<<< orphan*/  svn_fs_x__txn_id_t ;
struct TYPE_11__ {int /*<<< orphan*/  node; } ;
typedef  TYPE_2__ svn_fs_x__dag_path_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_13__ {int /*<<< orphan*/  kind; } ;
struct TYPE_12__ {int txn_flags; int /*<<< orphan*/  fs; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int SVN_FS_TXN_CHECK_LOCKS ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * add_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_match (TYPE_8__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_checksum_mismatch_err (TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_path_change_modify ; 
 int /*<<< orphan*/  svn_fs_x__allow_locked_operation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__dag_dup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__dag_file_checksum (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__dag_get_contents (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__dag_get_edit_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__get_dag_path (TYPE_2__**,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__make_path_mutable (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__root_txn_id (TYPE_3__*) ; 
 int /*<<< orphan*/  svn_node_file ; 
 int /*<<< orphan*/  svn_txdelta_apply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
apply_textdelta(void *baton,
                apr_pool_t *scratch_pool)
{
  txdelta_baton_t *tb = (txdelta_baton_t *) baton;
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

  if (tb->base_checksum)
    {
      svn_checksum_t *checksum;

      /* Until we finalize the node, its data_key points to the old
         contents, in other words, the base text. */
      SVN_ERR(svn_fs_x__dag_file_checksum(&checksum, tb->node,
                                          tb->base_checksum->kind,
                                          scratch_pool));
      if (!svn_checksum_match(tb->base_checksum, checksum))
        return svn_checksum_mismatch_err(tb->base_checksum, checksum,
                                         scratch_pool,
                                         _("Base checksum mismatch on '%s'"),
                                         tb->path);
    }

  /* Make a readable "source" stream out of the current contents of
     ROOT/PATH; obviously, this must done in the context of a db_txn.
     The stream is returned in tb->source_stream. */
  SVN_ERR(svn_fs_x__dag_get_contents(&(tb->source_stream),
                                     tb->node, tb->pool));

  /* Make a writable "target" stream */
  SVN_ERR(svn_fs_x__dag_get_edit_stream(&(tb->target_stream), tb->node,
                                        tb->pool));

  /* Now, create a custom window handler that uses our two streams. */
  svn_txdelta_apply(tb->source_stream,
                    tb->target_stream,
                    NULL,
                    tb->path,
                    tb->pool,
                    &(tb->interpreter),
                    &(tb->interpreter_baton));

  /* Make a record of this modification in the changes table. */
  return add_change(tb->root->fs, txn_id, tb->path,
                    svn_fs_path_change_modify, TRUE, FALSE, FALSE,
                    svn_node_file, SVN_INVALID_REVNUM, NULL, scratch_pool);
}