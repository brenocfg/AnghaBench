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
typedef  int /*<<< orphan*/  svn_ra_reporter3_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int /*<<< orphan*/  svn_delta_editor_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * make_reporter (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,void**,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
svn_ra_local__do_switch(svn_ra_session_t *session,
                        const svn_ra_reporter3_t **reporter,
                        void **report_baton,
                        svn_revnum_t update_revision,
                        const char *update_target,
                        svn_depth_t depth,
                        const char *switch_url,
                        svn_boolean_t send_copyfrom_args,
                        svn_boolean_t ignore_ancestry,
                        const svn_delta_editor_t *update_editor,
                        void *update_baton,
                        apr_pool_t *result_pool,
                        apr_pool_t *scratch_pool)
{
  return make_reporter(session,
                       reporter,
                       report_baton,
                       update_revision,
                       update_target,
                       switch_url,
                       TRUE /* text_deltas */,
                       depth,
                       send_copyfrom_args,
                       ignore_ancestry,
                       update_editor,
                       update_baton,
                       result_pool, scratch_pool);
}