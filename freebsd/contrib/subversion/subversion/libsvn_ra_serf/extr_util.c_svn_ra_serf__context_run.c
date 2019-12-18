#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ pending_error; scalar_t__ timeout; int /*<<< orphan*/  context; int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/ * (* cancel_func ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ svn_ra_serf__session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  scalar_t__ apr_interval_time_t ;

/* Variables and functions */
 scalar_t__ APR_STATUS_IS_TIMEUP (scalar_t__) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ SVN_ERR_BAD_CATEGORY_START ; 
 scalar_t__ SVN_ERR_LAST ; 
 scalar_t__ SVN_ERR_RA_DAV_CONN_TIMEOUT ; 
 int /*<<< orphan*/  SVN_ERR_W (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ SVN_NO_ERROR ; 
 scalar_t__ SVN_RA_SERF__CONTEXT_RUN_DURATION ; 
 int /*<<< orphan*/ * _ (char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ serf_context_run (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_error_create (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_ra_serf__wrap_err (scalar_t__,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_ra_serf__context_run(svn_ra_serf__session_t *sess,
                         apr_interval_time_t *waittime_left,
                         apr_pool_t *scratch_pool)
{
  apr_status_t status;
  svn_error_t *err;
  assert(sess->pending_error == SVN_NO_ERROR);

  if (sess->cancel_func)
    SVN_ERR(sess->cancel_func(sess->cancel_baton));

  status = serf_context_run(sess->context,
                            SVN_RA_SERF__CONTEXT_RUN_DURATION,
                            scratch_pool);

  err = sess->pending_error;
  sess->pending_error = SVN_NO_ERROR;

   /* If the context duration timeout is up, we'll subtract that
      duration from the total time alloted for such things.  If
      there's no time left, we fail with a message indicating that
      the connection timed out.  */
  if (APR_STATUS_IS_TIMEUP(status))
    {
      status = 0;

      if (sess->timeout)
        {
          if (*waittime_left > SVN_RA_SERF__CONTEXT_RUN_DURATION)
            {
              *waittime_left -= SVN_RA_SERF__CONTEXT_RUN_DURATION;
            }
          else
            {
              return
                  svn_error_compose_create(
                        err,
                        svn_error_create(SVN_ERR_RA_DAV_CONN_TIMEOUT, NULL,
                                         _("Connection timed out")));
            }
        }
    }
  else
    {
      *waittime_left = sess->timeout;
    }

  SVN_ERR(err);
  if (status)
    {
      /* ### This omits SVN_WARNING, and possibly relies on the fact that
         ### MAX(SERF_ERROR_*) < SVN_ERR_BAD_CATEGORY_START? */
      if (status >= SVN_ERR_BAD_CATEGORY_START && status < SVN_ERR_LAST)
        {
          /* apr can't translate subversion errors to text */
          SVN_ERR_W(svn_error_create(status, NULL, NULL),
                    _("Error running context"));
        }

      return svn_ra_serf__wrap_err(status, _("Error running context"));
    }

  return SVN_NO_ERROR;
}