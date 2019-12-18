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
typedef  int /*<<< orphan*/  svn_ra_session_t ;
typedef  int /*<<< orphan*/ * svn_commit_callback2_t ;
struct ccw_baton {void* original_baton; int /*<<< orphan*/ * original_callback; int /*<<< orphan*/ * session; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 struct ccw_baton* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * commit_callback_wrapper ; 

__attribute__((used)) static void
remap_commit_callback(svn_commit_callback2_t *callback,
                      void **callback_baton,
                      svn_ra_session_t *session,
                      svn_commit_callback2_t original_callback,
                      void *original_baton,
                      apr_pool_t *result_pool)
{
  if (original_callback == NULL)
    {
      *callback = NULL;
      *callback_baton = NULL;
    }
  else
    {
      /* Allocate this in RESULT_POOL, since the callback will be called
         long after this function has returned. */
      struct ccw_baton *ccwb = apr_palloc(result_pool, sizeof(*ccwb));

      ccwb->session = session;
      ccwb->original_callback = original_callback;
      ccwb->original_baton = original_baton;

      *callback = commit_callback_wrapper;
      *callback_baton = ccwb;
    }
}