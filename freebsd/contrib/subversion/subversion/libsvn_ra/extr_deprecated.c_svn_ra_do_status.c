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
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_6__ {TYPE_1__* vtable; } ;
typedef  TYPE_2__ svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_ra_reporter2_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_delta_editor_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct reporter_3in2_baton {int /*<<< orphan*/  reporter3_baton; int /*<<< orphan*/  reporter3; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_5__ {int /*<<< orphan*/ * (* do_status ) (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,void*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_DEPTH_INFINITY_OR_IMMEDIATES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 struct reporter_3in2_baton* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  reporter_3in2_wrapper ; 
 int /*<<< orphan*/ * stub1 (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,void*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_path_is_empty (char const*) ; 
 scalar_t__ svn_path_is_single_path_component (char const*) ; 

svn_error_t *svn_ra_do_status(svn_ra_session_t *session,
                              const svn_ra_reporter2_t **reporter,
                              void **report_baton,
                              const char *status_target,
                              svn_revnum_t revision,
                              svn_boolean_t recurse,
                              const svn_delta_editor_t *status_editor,
                              void *status_baton,
                              apr_pool_t *pool)
{
  struct reporter_3in2_baton *b = apr_palloc(pool, sizeof(*b));
  SVN_ERR_ASSERT(svn_path_is_empty(status_target)
                 || svn_path_is_single_path_component(status_target));
  *reporter = &reporter_3in2_wrapper;
  *report_baton = b;
  return session->vtable->do_status(session,
                                    &(b->reporter3), &(b->reporter3_baton),
                                    status_target, revision,
                                    SVN_DEPTH_INFINITY_OR_IMMEDIATES(recurse),
                                    status_editor, status_baton, pool);
}