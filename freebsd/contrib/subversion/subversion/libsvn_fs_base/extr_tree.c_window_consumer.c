#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  pool; TYPE_1__* root; int /*<<< orphan*/  target_stream; TYPE_3__* target_string; int /*<<< orphan*/  interpreter_baton; int /*<<< orphan*/  (* interpreter ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ txdelta_baton_t ;
typedef  int /*<<< orphan*/  svn_txdelta_window_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ apr_size_t ;
struct TYPE_7__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_5__ {int /*<<< orphan*/  fs; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ WRITE_BUFFER_SIZE ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__retry_txn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  svn_stringbuf_setempty (TYPE_3__*) ; 
 int /*<<< orphan*/  txn_body_txdelta_finalize_edits ; 

__attribute__((used)) static svn_error_t *
window_consumer(svn_txdelta_window_t *window, void *baton)
{
  txdelta_baton_t *tb = (txdelta_baton_t *) baton;

  /* Send the window right through to the custom window interpreter.
     In theory, the interpreter will then write more data to
     cb->target_string. */
  SVN_ERR(tb->interpreter(window, tb->interpreter_baton));

  /* ### the write_to_string() callback for the txdelta's output stream
     ### should be doing all the flush determination logic, not here.
     ### in a drastic case, a window could generate a LOT more than the
     ### maximum buffer size. we want to flush to the underlying target
     ### stream much sooner (e.g. also in a streamy fashion). also, by
     ### moving this logic inside the stream, the stream becomes nice
     ### and encapsulated: it holds all the logic about buffering and
     ### flushing.
     ###
     ### further: I believe the buffering should be removed from tree.c
     ### the buffering should go into the target_stream itself, which
     ### is defined by reps-string.c. Specifically, I think the
     ### rep_write_contents() function will handle the buffering and
     ### the spill to the underlying DB. by locating it there, then
     ### anybody who gets a writable stream for FS content can take
     ### advantage of the buffering capability. this will be important
     ### when we export an FS API function for writing a fulltext into
     ### the FS, rather than forcing that fulltext thru apply_textdelta.
  */

  /* Check to see if we need to purge the portion of the contents that
     have been written thus far. */
  if ((! window) || (tb->target_string->len > WRITE_BUFFER_SIZE))
    {
      apr_size_t len = tb->target_string->len;
      SVN_ERR(svn_stream_write(tb->target_stream,
                               tb->target_string->data,
                               &len));
      svn_stringbuf_setempty(tb->target_string);
    }

  /* Is the window NULL?  If so, we're done. */
  if (! window)
    {
      /* Close the internal-use stream.  ### This used to be inside of
         txn_body_fulltext_finalize_edits(), but that invoked a nested
         Berkeley DB transaction -- scandalous! */
      SVN_ERR(svn_stream_close(tb->target_stream));

      /* Tell the dag subsystem that we're finished with our edits. */
      SVN_ERR(svn_fs_base__retry_txn(tb->root->fs,
                                     txn_body_txdelta_finalize_edits, tb,
                                     FALSE, tb->pool));
    }

  return SVN_NO_ERROR;
}