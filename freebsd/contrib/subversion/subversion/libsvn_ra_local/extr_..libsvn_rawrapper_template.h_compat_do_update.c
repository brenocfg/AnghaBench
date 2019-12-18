#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_reporter_t ;
typedef  int /*<<< orphan*/  svn_ra_reporter3_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int /*<<< orphan*/  svn_delta_editor_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* do_update ) (void*,int /*<<< orphan*/  const**,void**,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_DEPTH_INFINITY_OR_FILES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_1__ VTBL ; 
 int /*<<< orphan*/  compat_wrap_reporter (int /*<<< orphan*/  const**,void**,int /*<<< orphan*/  const*,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (void*,int /*<<< orphan*/  const**,void**,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *compat_do_update(void *session_baton,
                                     const svn_ra_reporter_t **reporter,
                                     void **report_baton,
                                     svn_revnum_t revision_to_update_to,
                                     const char *update_target,
                                     svn_boolean_t recurse,
                                     const svn_delta_editor_t *editor,
                                     void *update_baton,
                                     apr_pool_t *pool)
{
  const svn_ra_reporter3_t *reporter3;
  void *baton3;
  svn_depth_t depth = SVN_DEPTH_INFINITY_OR_FILES(recurse);

  SVN_ERR(VTBL.do_update(session_baton, &reporter3, &baton3,
                         revision_to_update_to, update_target, depth,
                         FALSE /* send_copyfrom_args */,
                         FALSE /* ignore_ancestry */,
                         editor, update_baton,
                         pool, pool));
  compat_wrap_reporter(reporter, report_baton, reporter3, baton3, pool);

  return SVN_NO_ERROR;
}