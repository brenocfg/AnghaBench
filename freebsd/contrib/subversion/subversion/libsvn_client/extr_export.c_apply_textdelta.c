#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_txdelta_window_handler_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct handler_baton {int /*<<< orphan*/  apply_baton; int /*<<< orphan*/  apply_handler; int /*<<< orphan*/  tmppath; int /*<<< orphan*/ * pool; } ;
struct file_baton {int /*<<< orphan*/  text_digest; int /*<<< orphan*/  tmp_stream; int /*<<< orphan*/  tmppath; int /*<<< orphan*/  pool; int /*<<< orphan*/  path; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 struct handler_baton* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_dirent_dirname (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_del_none ; 
 int /*<<< orphan*/  svn_stream_disown (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_open_unique (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_txdelta_apply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  window_handler ; 

__attribute__((used)) static svn_error_t *
apply_textdelta(void *file_baton,
                const char *base_checksum,
                apr_pool_t *pool,
                svn_txdelta_window_handler_t *handler,
                void **handler_baton)
{
  struct file_baton *fb = file_baton;
  struct handler_baton *hb = apr_palloc(pool, sizeof(*hb));

  /* Create a temporary file in the same directory as the file. We're going
     to rename the thing into place when we're done. */
  SVN_ERR(svn_stream_open_unique(&fb->tmp_stream, &fb->tmppath,
                                 svn_dirent_dirname(fb->path, pool),
                                 svn_io_file_del_none, fb->pool, fb->pool));

  hb->pool = pool;
  hb->tmppath = fb->tmppath;

  /* svn_txdelta_apply() closes the stream, but we want to close it in the
     close_file() function, so disown it here. */
  /* ### contrast to when we call svn_ra_get_file() which does NOT close the
     ### tmp_stream. we *should* be much more consistent! */
  svn_txdelta_apply(svn_stream_empty(pool),
                    svn_stream_disown(fb->tmp_stream, pool),
                    fb->text_digest, NULL, pool,
                    &hb->apply_handler, &hb->apply_baton);

  *handler_baton = hb;
  *handler = window_handler;
  return SVN_NO_ERROR;
}