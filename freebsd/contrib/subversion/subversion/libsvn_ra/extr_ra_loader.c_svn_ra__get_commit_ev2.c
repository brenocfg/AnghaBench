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
struct TYPE_7__ {int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  cancel_func; TYPE_1__* vtable; } ;
typedef  TYPE_2__ svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_ra__provide_props_cb_t ;
typedef  int /*<<< orphan*/  svn_ra__provide_base_cb_t ;
typedef  int /*<<< orphan*/  svn_ra__get_copysrc_kind_cb_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_editor_t ;
typedef  int /*<<< orphan*/  svn_commit_callback2_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* get_commit_ev2 ) (int /*<<< orphan*/ **,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ **,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_ra__use_commit_shim (int /*<<< orphan*/ **,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_ra__get_commit_ev2(svn_editor_t **editor,
                       svn_ra_session_t *session,
                       apr_hash_t *revprop_table,
                       svn_commit_callback2_t commit_callback,
                       void *commit_baton,
                       apr_hash_t *lock_tokens,
                       svn_boolean_t keep_locks,
                       svn_ra__provide_base_cb_t provide_base_cb,
                       svn_ra__provide_props_cb_t provide_props_cb,
                       svn_ra__get_copysrc_kind_cb_t get_copysrc_kind_cb,
                       void *cb_baton,
                       apr_pool_t *result_pool,
                       apr_pool_t *scratch_pool)
{
  if (session->vtable->get_commit_ev2 == NULL)
    {
      /* The specific RA layer does not have an implementation. Use our
         default shim over the normal commit editor.  */

      return svn_error_trace(svn_ra__use_commit_shim(
                               editor,
                               session,
                               revprop_table,
                               commit_callback, commit_baton,
                               lock_tokens,
                               keep_locks,
                               provide_base_cb,
                               provide_props_cb,
                               get_copysrc_kind_cb,
                               cb_baton,
                               session->cancel_func, session->cancel_baton,
                               result_pool, scratch_pool));
    }

  /* Note: no need to remap the callback for Ev2. RA layers providing this
     vtable entry should completely fill in commit_info.  */

  return svn_error_trace(session->vtable->get_commit_ev2(
                           editor,
                           session,
                           revprop_table,
                           commit_callback, commit_baton,
                           lock_tokens,
                           keep_locks,
                           provide_base_cb,
                           provide_props_cb,
                           get_copysrc_kind_cb,
                           cb_baton,
                           session->cancel_func, session->cancel_baton,
                           result_pool, scratch_pool));
}