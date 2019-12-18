#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_7__ {TYPE_1__* vtable; } ;
typedef  TYPE_2__ svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_ra__replay_revstart_ev2_callback_t ;
typedef  int /*<<< orphan*/  svn_ra__replay_revfinish_ev2_callback_t ;
typedef  int /*<<< orphan*/  svn_ra__provide_props_cb_t ;
typedef  int /*<<< orphan*/  svn_ra__provide_base_cb_t ;
typedef  int /*<<< orphan*/  svn_ra__get_copysrc_kind_cb_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* replay_range_ev2 ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_ra__use_replay_range_shim (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_ra__replay_range_ev2(svn_ra_session_t *session,
                         svn_revnum_t start_revision,
                         svn_revnum_t end_revision,
                         svn_revnum_t low_water_mark,
                         svn_boolean_t send_deltas,
                         svn_ra__replay_revstart_ev2_callback_t revstart_func,
                         svn_ra__replay_revfinish_ev2_callback_t revfinish_func,
                         void *replay_baton,
                         svn_ra__provide_base_cb_t provide_base_cb,
                         svn_ra__provide_props_cb_t provide_props_cb,
                         svn_ra__get_copysrc_kind_cb_t get_copysrc_kind_cb,
                         void *cb_baton,
                         apr_pool_t *scratch_pool)
{
  if (session->vtable->replay_range_ev2 == NULL)
    {
      /* The specific RA layer does not have an implementation. Use our
         default shim over the normal replay editor.  */

      /* This will call the Ev1 replay range handler with modified
         callbacks. */
      return svn_error_trace(svn_ra__use_replay_range_shim(
                                session,
                                start_revision,
                                end_revision,
                                low_water_mark,
                                send_deltas,
                                revstart_func,
                                revfinish_func,
                                replay_baton,
                                provide_base_cb,
                                provide_props_cb,
                                cb_baton,
                                scratch_pool));
    }

  return svn_error_trace(session->vtable->replay_range_ev2(
                            session, start_revision, end_revision,
                            low_water_mark, send_deltas, revstart_func,
                            revfinish_func, replay_baton, scratch_pool));
}