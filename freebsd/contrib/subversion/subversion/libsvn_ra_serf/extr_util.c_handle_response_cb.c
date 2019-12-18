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
struct TYPE_5__ {scalar_t__ pending_error; } ;
typedef  TYPE_1__ svn_ra_serf__session_t ;
struct TYPE_6__ {void* done; void* discard_body; TYPE_1__* session; int /*<<< orphan*/  done_delegate_baton; int /*<<< orphan*/ * (* done_delegate ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  scheduled; } ;
typedef  TYPE_2__ svn_ra_serf__handler_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  serf_request_t ;
typedef  int /*<<< orphan*/  serf_bucket_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ APR_EAGAIN ; 
 scalar_t__ APR_EOF ; 
 scalar_t__ APR_STATUS_IS_EOF (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ SERF_BUCKET_READ_ERROR (scalar_t__) ; 
 void* TRUE ; 
 int /*<<< orphan*/  handle_response (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ save_error (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 

__attribute__((used)) static apr_status_t
handle_response_cb(serf_request_t *request,
                   serf_bucket_t *response,
                   void *baton,
                   apr_pool_t *response_pool)
{
  svn_ra_serf__handler_t *handler = baton;
  svn_error_t *err;
  apr_status_t inner_status;
  apr_status_t outer_status;
  apr_pool_t *scratch_pool = response_pool; /* Scratch pool needed? */

  err = svn_error_trace(handle_response(request, response,
                                        handler, &inner_status,
                                        scratch_pool));

  /* Select the right status value to return.  */
  outer_status = save_error(handler->session, err);
  if (!outer_status)
    outer_status = inner_status;

  /* Make sure the DONE flag is set properly and requests are cleaned up. */
  if (APR_STATUS_IS_EOF(outer_status) || APR_STATUS_IS_EOF(inner_status))
    {
      svn_ra_serf__session_t *sess = handler->session;
      handler->done = TRUE;
      handler->scheduled = FALSE;
      outer_status = APR_EOF;

      /* We use a cached handler->session here to allow handler to free the
         memory containing the handler */
      save_error(sess,
                 handler->done_delegate(request, handler->done_delegate_baton,
                                        scratch_pool));
    }
  else if (SERF_BUCKET_READ_ERROR(outer_status)
           && handler->session->pending_error)
    {
      handler->discard_body = TRUE; /* Discard further data */
      handler->done = TRUE; /* Mark as done */
      /* handler->scheduled is still TRUE, as we still expect data.
         If we would return an error outer-status the connection
         would have to be restarted. With scheduled still TRUE
         destroying the handler's pool will still reset the
         connection, avoiding the posibility of returning
         an error for this handler when a new request is
         scheduled. */
      outer_status = APR_EAGAIN; /* Exit context loop */
    }

  return outer_status;
}