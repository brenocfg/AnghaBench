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
struct txdelta_baton {int more_source; scalar_t__ buf; scalar_t__ pos; int /*<<< orphan*/ * context; int /*<<< orphan*/  more; int /*<<< orphan*/  result_pool; int /*<<< orphan*/  checksum; int /*<<< orphan*/  target; int /*<<< orphan*/  source; } ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ SVN_DELTA_WINDOW_SIZE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * compute_window (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_final (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_checksum_update (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  svn_stream_read_full (int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 

__attribute__((used)) static svn_error_t *
txdelta_next_window(svn_txdelta_window_t **window,
                    void *baton,
                    apr_pool_t *pool)
{
  struct txdelta_baton *b = baton;
  apr_size_t source_len = SVN_DELTA_WINDOW_SIZE;
  apr_size_t target_len = SVN_DELTA_WINDOW_SIZE;

  /* Read the source stream. */
  if (b->more_source)
    {
      SVN_ERR(svn_stream_read_full(b->source, b->buf, &source_len));
      b->more_source = (source_len == SVN_DELTA_WINDOW_SIZE);
    }
  else
    source_len = 0;

  /* Read the target stream. */
  SVN_ERR(svn_stream_read_full(b->target, b->buf + source_len, &target_len));
  b->pos += source_len;

  if (target_len == 0)
    {
      /* No target data?  We're done; return the final window. */
      if (b->context != NULL)
        SVN_ERR(svn_checksum_final(&b->checksum, b->context, b->result_pool));

      *window = NULL;
      b->more = FALSE;
      return SVN_NO_ERROR;
    }
  else if (b->context != NULL)
    SVN_ERR(svn_checksum_update(b->context, b->buf + source_len, target_len));

  *window = compute_window(b->buf, source_len, target_len,
                           b->pos - source_len, pool);

  /* That's it. */
  return SVN_NO_ERROR;
}