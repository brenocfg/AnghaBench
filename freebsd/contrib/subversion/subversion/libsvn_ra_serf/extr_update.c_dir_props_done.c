#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int code; } ;
struct TYPE_10__ {TYPE_1__ sline; scalar_t__ server_error; } ;
typedef  TYPE_3__ svn_ra_serf__handler_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  serf_request_t ;
struct TYPE_11__ {TYPE_2__* ctx; TYPE_3__* propfind_handler; } ;
typedef  TYPE_4__ dir_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_9__ {int /*<<< orphan*/  num_active_propfinds; } ;

/* Variables and functions */
 int /*<<< orphan*/  maybe_close_dir (TYPE_4__*) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_ra_serf__server_error_create (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__unexpected_status (TYPE_3__*) ; 

__attribute__((used)) static svn_error_t *
dir_props_done(serf_request_t *request,
               void *baton,
               apr_pool_t *scratch_pool)
{
  dir_baton_t *dir = baton;
  svn_ra_serf__handler_t *handler = dir->propfind_handler;

  if (handler->server_error)
    return svn_ra_serf__server_error_create(handler, scratch_pool);

  if (handler->sline.code != 207)
    return svn_error_trace(svn_ra_serf__unexpected_status(handler));

  dir->ctx->num_active_propfinds--;

  /* Closing the directory will automatically deliver the propfind props.
   *
   * Note that closing the directory may dispose the pool containing the
   * handler, which is only a valid operation in this callback, as after
   * this callback serf assumes the request is done. */

  return svn_error_trace(maybe_close_dir(dir));
}