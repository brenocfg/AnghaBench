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
typedef  int /*<<< orphan*/  svn_ra_reporter3_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int /*<<< orphan*/  svn_delta_editor_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_5__ {int /*<<< orphan*/ * (* do_switch ) (TYPE_2__*,int /*<<< orphan*/  const**,void**,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * stub1 (TYPE_2__*,int /*<<< orphan*/  const**,void**,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_path_is_empty (char const*) ; 
 scalar_t__ svn_path_is_single_path_component (char const*) ; 

svn_error_t *
svn_ra_do_switch3(svn_ra_session_t *session,
                  const svn_ra_reporter3_t **reporter,
                  void **report_baton,
                  svn_revnum_t revision_to_switch_to,
                  const char *switch_target,
                  svn_depth_t depth,
                  const char *switch_url,
                  svn_boolean_t send_copyfrom_args,
                  svn_boolean_t ignore_ancestry,
                  const svn_delta_editor_t *switch_editor,
                  void *switch_baton,
                  apr_pool_t *result_pool,
                  apr_pool_t *scratch_pool)
{
  SVN_ERR_ASSERT(svn_path_is_empty(switch_target)
                 || svn_path_is_single_path_component(switch_target));
  return session->vtable->do_switch(session,
                                    reporter, report_baton,
                                    revision_to_switch_to, switch_target,
                                    depth, switch_url,
                                    send_copyfrom_args,
                                    ignore_ancestry,
                                    switch_editor,
                                    switch_baton,
                                    result_pool, scratch_pool);
}