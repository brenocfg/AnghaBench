#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ version; } ;
struct TYPE_8__ {TYPE_2__* conn; scalar_t__ scheduled; void* discard_body; void* reading_body; int /*<<< orphan*/ * location; TYPE_1__ sline; int /*<<< orphan*/ * server_error; void* done; int /*<<< orphan*/ * handler_pool; } ;
typedef  TYPE_3__ svn_ra_serf__handler_t ;
struct TYPE_7__ {int /*<<< orphan*/  conn; } ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT_NO_RETURN (int) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  serf_connection_request_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  setup_request_cb ; 

void
svn_ra_serf__request_create(svn_ra_serf__handler_t *handler)
{
  SVN_ERR_ASSERT_NO_RETURN(handler->handler_pool != NULL
                           && !handler->scheduled);

  /* In case HANDLER is re-queued, reset the various transient fields. */
  handler->done = FALSE;
  handler->server_error = NULL;
  handler->sline.version = 0;
  handler->location = NULL;
  handler->reading_body = FALSE;
  handler->discard_body = FALSE;
  handler->scheduled = TRUE;

  /* Keeping track of the returned request object would be nice, but doesn't
     work the way we would expect in ra_serf..

     Serf sometimes creates a new request for us (and destroys the old one)
     without telling, like when authentication failed (401/407 response.

     We 'just' trust serf to do the right thing and expect it to tell us
     when the state of the request changes.

     ### I fixed a request leak in serf in r2258 on auth failures.
   */
  (void) serf_connection_request_create(handler->conn->conn,
                                        setup_request_cb, handler);
}