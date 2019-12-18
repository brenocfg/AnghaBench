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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_ra__replay_revstart_ev2_callback_t ;
typedef  int /*<<< orphan*/  svn_ra__replay_revfinish_ev2_callback_t ;
typedef  int /*<<< orphan*/  svn_ra__provide_props_cb_t ;
typedef  int /*<<< orphan*/  svn_ra__provide_base_cb_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct wrapped_replay_baton_t {void* cb_baton; int /*<<< orphan*/  provide_props_cb; int /*<<< orphan*/  provide_base_cb; int /*<<< orphan*/ * session; void* replay_baton; int /*<<< orphan*/  revfinish_func; int /*<<< orphan*/  revstart_func; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 struct wrapped_replay_baton_t* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  revfinish_func_wrapper ; 
 int /*<<< orphan*/  revstart_func_wrapper ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_ra_replay_range (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wrapped_replay_baton_t*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_ra__use_replay_range_shim(svn_ra_session_t *session,
                              svn_revnum_t start_revision,
                              svn_revnum_t end_revision,
                              svn_revnum_t low_water_mark,
                              svn_boolean_t send_deltas,
                              svn_ra__replay_revstart_ev2_callback_t revstart_func,
                              svn_ra__replay_revfinish_ev2_callback_t revfinish_func,
                              void *replay_baton,
                              svn_ra__provide_base_cb_t provide_base_cb,
                              svn_ra__provide_props_cb_t provide_props_cb,
                              void *cb_baton,
                              apr_pool_t *scratch_pool)
{
  /* The basic strategy here is to wrap the callback start and finish
     functions to appropriately return an Ev1 editor which is itself wrapped
     from the Ev2 one the provided callbacks will give us. */

  struct wrapped_replay_baton_t *wrb = apr_pcalloc(scratch_pool, sizeof(*wrb));

  wrb->revstart_func = revstart_func;
  wrb->revfinish_func = revfinish_func;
  wrb->replay_baton = replay_baton;
  wrb->session = session;

  wrb->provide_base_cb = provide_base_cb;
  wrb->provide_props_cb = provide_props_cb;
  wrb->cb_baton = cb_baton;

  return svn_error_trace(svn_ra_replay_range(session, start_revision,
                                             end_revision, low_water_mark,
                                             send_deltas,
                                             revstart_func_wrapper,
                                             revfinish_func_wrapper,
                                             wrb, scratch_pool));
}