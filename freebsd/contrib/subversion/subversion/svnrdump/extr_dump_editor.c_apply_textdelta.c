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
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct file_baton {int /*<<< orphan*/  pool; int /*<<< orphan*/  base_checksum; int /*<<< orphan*/  dump_text; struct dump_edit_baton* eb; } ;
struct dump_edit_baton {int /*<<< orphan*/  delta_file; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_DELTA_COMPRESSION_LEVEL_DEFAULT ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * svn_stream_from_aprfile2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_txdelta_to_svndiff3 (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
apply_textdelta(void *file_baton, const char *base_checksum,
                apr_pool_t *pool,
                svn_txdelta_window_handler_t *handler,
                void **handler_baton)
{
  struct file_baton *fb = file_baton;
  struct dump_edit_baton *eb = fb->eb;
  svn_stream_t *delta_filestream;

  /* Use a temporary file to measure the Text-content-length */
  delta_filestream = svn_stream_from_aprfile2(eb->delta_file, TRUE, pool);

  /* Prepare to write the delta to the delta_filestream */
  svn_txdelta_to_svndiff3(handler, handler_baton,
                          delta_filestream, 0,
                          SVN_DELTA_COMPRESSION_LEVEL_DEFAULT, pool);

  /* Record that there's text to be dumped, and its base checksum. */
  fb->dump_text = TRUE;
  fb->base_checksum = apr_pstrdup(fb->pool, base_checksum);

  return SVN_NO_ERROR;
}