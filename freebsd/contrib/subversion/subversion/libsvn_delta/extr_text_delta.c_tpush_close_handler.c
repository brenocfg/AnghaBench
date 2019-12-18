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
struct tpush_baton {scalar_t__ target_len; int /*<<< orphan*/  whb; int /*<<< orphan*/ * (* wh ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  pool; int /*<<< orphan*/  source_offset; int /*<<< orphan*/  source_len; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * compute_window (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
tpush_close_handler(void *baton)
{
  struct tpush_baton *tb = baton;
  svn_txdelta_window_t *window;

  /* Send a final window if we have any residual target data. */
  if (tb->target_len > 0)
    {
      window = compute_window(tb->buf, tb->source_len, tb->target_len,
                              tb->source_offset, tb->pool);
      SVN_ERR(tb->wh(window, tb->whb));
    }

  /* Send a final NULL window signifying the end. */
  return tb->wh(NULL, tb->whb);
}