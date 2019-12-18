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
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_7__ {TYPE_3__* priv; } ;
typedef  TYPE_2__ svn_ra_session_t ;
struct TYPE_6__ {int /*<<< orphan*/  path; } ;
struct TYPE_8__ {TYPE_1__ session_url; } ;
typedef  TYPE_3__ svn_ra_serf__session_t ;
typedef  int /*<<< orphan*/  svn_ra_reporter3_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int /*<<< orphan*/  svn_delta_editor_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * make_update_reporter (TYPE_2__*,int /*<<< orphan*/  const**,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_ra_serf__do_switch(svn_ra_session_t *ra_session,
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
  svn_ra_serf__session_t *session = ra_session->priv;

  return make_update_reporter(ra_session, reporter, report_baton,
                              revision_to_switch_to,
                              session->session_url.path,
                              switch_url, switch_target,
                              depth,
                              ignore_ancestry,
                              TRUE /* text_deltas */,
                              send_copyfrom_args,
                              switch_editor, switch_baton,
                              result_pool, scratch_pool);
}