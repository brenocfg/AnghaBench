#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ scheduled; int /*<<< orphan*/  session; int /*<<< orphan*/  done; } ;
typedef  TYPE_1__ svn_ra_serf__handler_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_ra_serf__context_run_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__request_create (TYPE_1__*) ; 
 int /*<<< orphan*/  svn_ra_serf__unschedule_handler (TYPE_1__*) ; 

svn_error_t *
svn_ra_serf__context_run_one(svn_ra_serf__handler_t *handler,
                             apr_pool_t *scratch_pool)
{
  svn_error_t *err;

  /* Create a serf request based on HANDLER.  */
  svn_ra_serf__request_create(handler);

  /* Wait until the response logic marks its DONE status.  */
  err = svn_ra_serf__context_run_wait(&handler->done, handler->session,
                                      scratch_pool);

  if (handler->scheduled)
    {
      /* We reset the connection (breaking  pipelining, etc.), as
         if we didn't the next data would still be handled by this handler,
         which is done as far as our caller is concerned. */
      svn_ra_serf__unschedule_handler(handler);
    }

  return svn_error_trace(err);
}