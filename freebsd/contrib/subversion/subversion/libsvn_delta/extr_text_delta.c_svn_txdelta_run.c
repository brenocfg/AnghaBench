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
typedef  int /*<<< orphan*/  (* svn_txdelta_window_handler_t ) (int /*<<< orphan*/ *,void*) ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  int /*<<< orphan*/  svn_checksum_kind_t ;
typedef  int /*<<< orphan*/  (* svn_cancel_func_t ) (void*) ;
struct txdelta_baton {int /*<<< orphan*/ * checksum; int /*<<< orphan*/  context; int /*<<< orphan*/ * result_pool; int /*<<< orphan*/  buf; scalar_t__ pos; void* more; void* more_source; int /*<<< orphan*/ * target; int /*<<< orphan*/ * source; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int SVN_DELTA_WINDOW_SIZE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 void* TRUE ; 
 int /*<<< orphan*/  apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  svn_checksum_ctx_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txdelta_next_window (int /*<<< orphan*/ **,struct txdelta_baton*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_txdelta_run(svn_stream_t *source,
                svn_stream_t *target,
                svn_txdelta_window_handler_t handler,
                void *handler_baton,
                svn_checksum_kind_t checksum_kind,
                svn_checksum_t **checksum,
                svn_cancel_func_t cancel_func,
                void *cancel_baton,
                apr_pool_t *result_pool,
                apr_pool_t *scratch_pool)
{
  apr_pool_t *iterpool = svn_pool_create(scratch_pool);
  struct txdelta_baton tb = { 0 };
  svn_txdelta_window_t *window;

  tb.source = source;
  tb.target = target;
  tb.more_source = TRUE;
  tb.more = TRUE;
  tb.pos = 0;
  tb.buf = apr_palloc(scratch_pool, 2 * SVN_DELTA_WINDOW_SIZE);
  tb.result_pool = result_pool;

  if (checksum != NULL)
    tb.context = svn_checksum_ctx_create(checksum_kind, scratch_pool);

  do
    {
      /* free the window (if any) */
      svn_pool_clear(iterpool);

      /* read in a single delta window */
      SVN_ERR(txdelta_next_window(&window, &tb, iterpool));

      /* shove it at the handler */
      SVN_ERR((*handler)(window, handler_baton));

      if (cancel_func)
        SVN_ERR(cancel_func(cancel_baton));
    }
  while (window != NULL);

  svn_pool_destroy(iterpool);

  if (checksum != NULL)
    *checksum = tb.checksum;  /* should be there! */

  return SVN_NO_ERROR;
}