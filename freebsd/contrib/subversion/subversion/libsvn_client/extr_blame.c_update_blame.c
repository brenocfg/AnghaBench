#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct file_rev_baton {int /*<<< orphan*/ * currpool; int /*<<< orphan*/ * lastpool; int /*<<< orphan*/  last_filename; int /*<<< orphan*/ * filepool; int /*<<< orphan*/  last_original_filename; int /*<<< orphan*/ * prevfilepool; TYPE_1__* ctx; int /*<<< orphan*/  diff_options; struct blame_chain* chain; scalar_t__ include_merged_revisions; struct blame_chain* merged_chain; } ;
struct delta_baton {int /*<<< orphan*/  filename; int /*<<< orphan*/  rev; int /*<<< orphan*/  is_merged_revision; scalar_t__ source_stream; struct file_rev_baton* file_rev_baton; } ;
struct blame_chain {int dummy; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_2__ {int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  cancel_func; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  add_file_blame (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct blame_chain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_close (scalar_t__) ; 

__attribute__((used)) static svn_error_t *
update_blame(void *baton)
{
  struct delta_baton *dbaton = baton;
  struct file_rev_baton *frb = dbaton->file_rev_baton;
  struct blame_chain *chain;

  /* Close the source file used for the delta.
     It is important to do this early, since otherwise, they will be deleted
     before all handles are closed, which leads to failures on some platforms
     when new tempfiles are to be created. */
  if (dbaton->source_stream)
    SVN_ERR(svn_stream_close(dbaton->source_stream));

  /* If we are including merged revisions, we need to add each rev to the
     merged chain. */
  if (frb->include_merged_revisions)
    chain = frb->merged_chain;
  else
    chain = frb->chain;

  /* Process this file. */
  SVN_ERR(add_file_blame(frb->last_filename,
                         dbaton->filename, chain, dbaton->rev,
                         frb->diff_options,
                         frb->ctx->cancel_func, frb->ctx->cancel_baton,
                         frb->currpool));

  /* If we are including merged revisions, and the current revision is not a
     merged one, we need to add its blame info to the chain for the original
     line of history. */
  if (frb->include_merged_revisions && ! dbaton->is_merged_revision)
    {
      apr_pool_t *tmppool;

      SVN_ERR(add_file_blame(frb->last_original_filename,
                             dbaton->filename, frb->chain, dbaton->rev,
                             frb->diff_options,
                             frb->ctx->cancel_func, frb->ctx->cancel_baton,
                             frb->currpool));

      /* This filename could be around for a while, potentially, so
         use the longer lifetime pool, and switch it with the previous one*/
      svn_pool_clear(frb->prevfilepool);
      tmppool = frb->filepool;
      frb->filepool = frb->prevfilepool;
      frb->prevfilepool = tmppool;

      frb->last_original_filename = apr_pstrdup(frb->filepool,
                                                dbaton->filename);
    }

  /* Prepare for next revision. */

  /* Remember the file name so we can diff it with the next revision. */
  frb->last_filename = dbaton->filename;

  /* Switch pools. */
  {
    apr_pool_t *tmp_pool = frb->lastpool;
    frb->lastpool = frb->currpool;
    frb->currpool = tmp_pool;
  }

  return SVN_NO_ERROR;
}