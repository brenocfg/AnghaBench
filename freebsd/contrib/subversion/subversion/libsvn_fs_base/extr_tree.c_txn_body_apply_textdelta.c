#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_13__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/  interpreter_baton; int /*<<< orphan*/  interpreter; int /*<<< orphan*/  pool; int /*<<< orphan*/  path; int /*<<< orphan*/  string_stream; int /*<<< orphan*/  source_stream; int /*<<< orphan*/  target_string; int /*<<< orphan*/  node; int /*<<< orphan*/  target_stream; TYPE_10__* base_checksum; TYPE_13__* root; } ;
typedef  TYPE_1__ txdelta_baton_t ;
struct TYPE_21__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_2__ trail_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
struct TYPE_22__ {int /*<<< orphan*/  node; } ;
typedef  TYPE_3__ parent_path_t ;
struct TYPE_19__ {char* txn; int txn_flags; } ;
struct TYPE_18__ {int /*<<< orphan*/  kind; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int SVN_FS_TXN_CHECK_LOCKS ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  make_path_mutable (TYPE_13__*,TYPE_3__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open_path (TYPE_3__**,TYPE_13__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_checksum_match (TYPE_10__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_checksum_mismatch_err (TYPE_10__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__allow_locked_operation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__dag_file_checksum (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__dag_get_contents (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__dag_get_edit_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_create (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stringbuf_create_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_txdelta_apply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_to_string ; 

__attribute__((used)) static svn_error_t *
txn_body_apply_textdelta(void *baton, trail_t *trail)
{
  txdelta_baton_t *tb = (txdelta_baton_t *) baton;
  parent_path_t *parent_path;
  const char *txn_id = tb->root->txn;

  /* Call open_path with no flags, as we want this to return an error
     if the node for which we are searching doesn't exist. */
  SVN_ERR(open_path(&parent_path, tb->root, tb->path, 0, txn_id,
                    trail, trail->pool));

  /* Check to see if path is locked;  if so, check that we can use it. */
  if (tb->root->txn_flags & SVN_FS_TXN_CHECK_LOCKS)
    SVN_ERR(svn_fs_base__allow_locked_operation(tb->path, FALSE,
                                                trail, trail->pool));

  /* Now, make sure this path is mutable. */
  SVN_ERR(make_path_mutable(tb->root, parent_path, tb->path,
                            trail, trail->pool));
  tb->node = parent_path->node;

  if (tb->base_checksum)
    {
      svn_checksum_t *checksum;

      /* Until we finalize the node, its data_key points to the old
         contents, in other words, the base text. */
      SVN_ERR(svn_fs_base__dag_file_checksum(&checksum,
                                             tb->base_checksum->kind,
                                             tb->node, trail, trail->pool));
      /* TODO: This only compares checksums if they are the same kind, but
         we're calculating both SHA1 and MD5 checksums somewhere in
         reps-strings.c.  Could we keep them both around somehow so this
         check could be more comprehensive? */
      if (!svn_checksum_match(tb->base_checksum, checksum))
        return svn_checksum_mismatch_err(tb->base_checksum, checksum,
                            trail->pool,
                            _("Base checksum mismatch on '%s'"),
                            tb->path);
    }

  /* Make a readable "source" stream out of the current contents of
     ROOT/PATH; obviously, this must done in the context of a db_txn.
     The stream is returned in tb->source_stream. */
  SVN_ERR(svn_fs_base__dag_get_contents(&(tb->source_stream),
                                        tb->node, trail, tb->pool));

  /* Make a writable "target" stream */
  SVN_ERR(svn_fs_base__dag_get_edit_stream(&(tb->target_stream), tb->node,
                                           txn_id, trail, tb->pool));

  /* Make a writable "string" stream which writes data to
     tb->target_string. */
  tb->target_string = svn_stringbuf_create_empty(tb->pool);
  tb->string_stream = svn_stream_create(tb, tb->pool);
  svn_stream_set_write(tb->string_stream, write_to_string);

  /* Now, create a custom window handler that uses our two streams. */
  svn_txdelta_apply(tb->source_stream,
                    tb->string_stream,
                    NULL,
                    tb->path,
                    tb->pool,
                    &(tb->interpreter),
                    &(tb->interpreter_baton));

  return SVN_NO_ERROR;
}