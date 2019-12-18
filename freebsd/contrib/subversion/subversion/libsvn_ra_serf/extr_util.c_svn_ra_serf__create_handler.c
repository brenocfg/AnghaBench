#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * conns; } ;
typedef  TYPE_1__ svn_ra_serf__session_t ;
struct TYPE_8__ {int /*<<< orphan*/  done_delegate; struct TYPE_8__* done_delegate_baton; int /*<<< orphan*/  conn; TYPE_1__* session; int /*<<< orphan*/ * handler_pool; } ;
typedef  TYPE_2__ svn_ra_serf__handler_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_2__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pool_cleanup_null ; 
 int /*<<< orphan*/  apr_pool_cleanup_register (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handler_cleanup ; 
 int /*<<< orphan*/  response_done ; 

svn_ra_serf__handler_t *
svn_ra_serf__create_handler(svn_ra_serf__session_t *session,
                            apr_pool_t *result_pool)
{
  svn_ra_serf__handler_t *handler;

  handler = apr_pcalloc(result_pool, sizeof(*handler));
  handler->handler_pool = result_pool;

  apr_pool_cleanup_register(result_pool, handler, handler_cleanup,
                            apr_pool_cleanup_null);

  handler->session = session;
  handler->conn = session->conns[0];

  /* Setup the default done handler, to handle server errors */
  handler->done_delegate_baton = handler;
  handler->done_delegate = response_done;

  return handler;
}