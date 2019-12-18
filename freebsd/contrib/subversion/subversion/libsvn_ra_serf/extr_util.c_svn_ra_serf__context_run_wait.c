#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ pending_error; int num_conns; TYPE_1__** conns; int /*<<< orphan*/  timeout; } ;
typedef  TYPE_2__ svn_ra_serf__session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_interval_time_t ;
struct TYPE_5__ {int /*<<< orphan*/  bkt_alloc; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_NO_ERROR ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  serf_debug__closed_conn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__context_run (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_ra_serf__context_run_wait(svn_boolean_t *done,
                              svn_ra_serf__session_t *sess,
                              apr_pool_t *scratch_pool)
{
  apr_pool_t *iterpool;
  apr_interval_time_t waittime_left = sess->timeout;

  assert(sess->pending_error == SVN_NO_ERROR);

  iterpool = svn_pool_create(scratch_pool);
  while (!*done)
    {
      int i;

      svn_pool_clear(iterpool);

      SVN_ERR(svn_ra_serf__context_run(sess, &waittime_left, iterpool));

      /* Debugging purposes only! */
      for (i = 0; i < sess->num_conns; i++)
        {
          serf_debug__closed_conn(sess->conns[i]->bkt_alloc);
        }
    }
  svn_pool_destroy(iterpool);

  return SVN_NO_ERROR;
}