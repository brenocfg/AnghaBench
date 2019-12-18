#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  response_baton; int /*<<< orphan*/  response_handler; int /*<<< orphan*/  xmlctx; int /*<<< orphan*/ * pool; TYPE_3__* handler; int /*<<< orphan*/  items; } ;
typedef  TYPE_2__ svn_ra_serf__server_error_t ;
struct TYPE_8__ {int code; } ;
struct TYPE_10__ {int /*<<< orphan*/  response_baton; int /*<<< orphan*/  response_handler; TYPE_1__ sline; int /*<<< orphan*/  session; } ;
typedef  TYPE_3__ svn_ra_serf__handler_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  expected_status ;
typedef  int /*<<< orphan*/  error_item_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_array_make (int /*<<< orphan*/ *,int,int) ; 
 void* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  multistatus_closed ; 
 int /*<<< orphan*/  multistatus_opened ; 
 int /*<<< orphan*/  multistatus_ttable ; 
 TYPE_3__* svn_ra_serf__create_expat_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__xml_context_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_ra_serf__setup_error_parsing(svn_ra_serf__server_error_t **server_err,
                                 svn_ra_serf__handler_t *handler,
                                 svn_boolean_t expect_207_only,
                                 apr_pool_t *result_pool,
                                 apr_pool_t *scratch_pool)
{
  svn_ra_serf__server_error_t *ms_baton;
  svn_ra_serf__handler_t *tmp_handler;

  int *expected_status = apr_pcalloc(result_pool,
                                     2 * sizeof(expected_status[0]));

  expected_status[0] = handler->sline.code;

  ms_baton = apr_pcalloc(result_pool, sizeof(*ms_baton));
  ms_baton->pool = result_pool;

  ms_baton->items = apr_array_make(result_pool, 4, sizeof(error_item_t *));
  ms_baton->handler = handler;

  ms_baton->xmlctx = svn_ra_serf__xml_context_create(multistatus_ttable,
                                                     multistatus_opened,
                                                     multistatus_closed,
                                                     NULL,
                                                     ms_baton,
                                                     ms_baton->pool);

  tmp_handler = svn_ra_serf__create_expat_handler(handler->session,
                                                  ms_baton->xmlctx,
                                                  expected_status,
                                                  result_pool);

  /* Ugly way to obtain expat_handler() */
  tmp_handler->sline = handler->sline;
  ms_baton->response_handler = tmp_handler->response_handler;
  ms_baton->response_baton = tmp_handler->response_baton;

  *server_err = ms_baton;
  return SVN_NO_ERROR;
}