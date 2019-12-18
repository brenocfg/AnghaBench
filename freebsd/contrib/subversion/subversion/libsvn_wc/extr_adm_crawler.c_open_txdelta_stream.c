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
typedef  int /*<<< orphan*/  svn_txdelta_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_2__ {scalar_t__ need_reset; int /*<<< orphan*/  local_stream; int /*<<< orphan*/  base_stream; } ;
typedef  TYPE_1__ open_txdelta_stream_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  svn_stream_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_txdelta2 (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
open_txdelta_stream(svn_txdelta_stream_t **txdelta_stream_p,
                    void *baton,
                    apr_pool_t *result_pool,
                    apr_pool_t *scratch_pool)
{
  open_txdelta_stream_baton_t *b = baton;

  if (b->need_reset)
    {
      /* Under rare circumstances, we can be restarted and would need to
       * supply the delta stream again.  In this case, reset both streams. */
      SVN_ERR(svn_stream_reset(b->base_stream));
      SVN_ERR(svn_stream_reset(b->local_stream));
    }

  svn_txdelta2(txdelta_stream_p, b->base_stream, b->local_stream,
               FALSE, result_pool);
  b->need_reset = TRUE;
  return SVN_NO_ERROR;
}