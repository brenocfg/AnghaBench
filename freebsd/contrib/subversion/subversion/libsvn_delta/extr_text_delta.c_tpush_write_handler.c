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
typedef  int /*<<< orphan*/  svn_txdelta_window_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct tpush_baton {scalar_t__ source_len; scalar_t__ buf; scalar_t__ target_len; int /*<<< orphan*/  source_offset; int /*<<< orphan*/  whb; int /*<<< orphan*/  (* wh ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;scalar_t__ source_done; int /*<<< orphan*/  source; int /*<<< orphan*/  pool; } ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ SVN_DELTA_WINDOW_SIZE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/ * compute_window (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char const*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_read_full (int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 

__attribute__((used)) static svn_error_t *
tpush_write_handler(void *baton, const char *data, apr_size_t *len)
{
  struct tpush_baton *tb = baton;
  apr_size_t chunk_len, data_len = *len;
  apr_pool_t *pool = svn_pool_create(tb->pool);
  svn_txdelta_window_t *window;

  while (data_len > 0)
    {
      svn_pool_clear(pool);

      /* Make sure we're all full up on source data, if possible. */
      if (tb->source_len == 0 && !tb->source_done)
        {
          tb->source_len = SVN_DELTA_WINDOW_SIZE;
          SVN_ERR(svn_stream_read_full(tb->source, tb->buf, &tb->source_len));
          if (tb->source_len < SVN_DELTA_WINDOW_SIZE)
            tb->source_done = TRUE;
        }

      /* Copy in the target data, up to SVN_DELTA_WINDOW_SIZE. */
      chunk_len = SVN_DELTA_WINDOW_SIZE - tb->target_len;
      if (chunk_len > data_len)
        chunk_len = data_len;
      memcpy(tb->buf + tb->source_len + tb->target_len, data, chunk_len);
      data += chunk_len;
      data_len -= chunk_len;
      tb->target_len += chunk_len;

      /* If we're full of target data, compute and fire off a window. */
      if (tb->target_len == SVN_DELTA_WINDOW_SIZE)
        {
          window = compute_window(tb->buf, tb->source_len, tb->target_len,
                                  tb->source_offset, pool);
          SVN_ERR(tb->wh(window, tb->whb));
          tb->source_offset += tb->source_len;
          tb->source_len = 0;
          tb->target_len = 0;
        }
    }

  svn_pool_destroy(pool);
  return SVN_NO_ERROR;
}