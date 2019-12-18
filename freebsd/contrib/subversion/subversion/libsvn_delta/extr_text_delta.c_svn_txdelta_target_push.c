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
struct tpush_baton {scalar_t__ target_len; int /*<<< orphan*/  source_done; scalar_t__ source_len; scalar_t__ source_offset; void* buf; int /*<<< orphan*/ * pool; void* whb; int /*<<< orphan*/  wh; int /*<<< orphan*/ * source; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int SVN_DELTA_WINDOW_SIZE ; 
 void* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * svn_stream_create (struct tpush_baton*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_set_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpush_close_handler ; 
 int /*<<< orphan*/  tpush_write_handler ; 

svn_stream_t *
svn_txdelta_target_push(svn_txdelta_window_handler_t handler,
                        void *handler_baton, svn_stream_t *source,
                        apr_pool_t *pool)
{
  struct tpush_baton *tb;
  svn_stream_t *stream;

  /* Initialize baton. */
  tb = apr_palloc(pool, sizeof(*tb));
  tb->source = source;
  tb->wh = handler;
  tb->whb = handler_baton;
  tb->pool = pool;
  tb->buf = apr_palloc(pool, 2 * SVN_DELTA_WINDOW_SIZE);
  tb->source_offset = 0;
  tb->source_len = 0;
  tb->source_done = FALSE;
  tb->target_len = 0;

  /* Create and return writable stream. */
  stream = svn_stream_create(tb, pool);
  svn_stream_set_write(stream, tpush_write_handler);
  svn_stream_set_close(stream, tpush_close_handler);
  return stream;
}