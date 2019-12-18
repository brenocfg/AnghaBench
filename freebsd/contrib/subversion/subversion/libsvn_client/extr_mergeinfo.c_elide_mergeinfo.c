#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  prop_state; } ;
typedef  TYPE_1__ svn_wc_notify_t ;
typedef  int /*<<< orphan*/  svn_mergeinfo_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_8__ {int /*<<< orphan*/  notify_baton2; int /*<<< orphan*/  (* notify_func2 ) (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  wc_ctx; } ;
typedef  TYPE_2__ svn_client_ctx_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_MERGEINFO ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  should_elide_mergeinfo (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_depth_empty ; 
 int /*<<< orphan*/  svn_dirent_is_absolute (char const*) ; 
 TYPE_1__* svn_wc_create_notify (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_notify_merge_elide_info ; 
 int /*<<< orphan*/  svn_wc_notify_state_changed ; 
 int /*<<< orphan*/  svn_wc_notify_update_update ; 
 int /*<<< orphan*/  svn_wc_prop_set4 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
elide_mergeinfo(svn_mergeinfo_t parent_mergeinfo,
                svn_mergeinfo_t child_mergeinfo,
                const char *local_abspath,
                svn_client_ctx_t *ctx,
                apr_pool_t *scratch_pool)
{
  svn_boolean_t elides;

  SVN_ERR_ASSERT(svn_dirent_is_absolute(local_abspath));

  SVN_ERR(should_elide_mergeinfo(&elides,
                                 parent_mergeinfo, child_mergeinfo, NULL,
                                 scratch_pool));

  if (elides)
    {
      SVN_ERR(svn_wc_prop_set4(ctx->wc_ctx, local_abspath, SVN_PROP_MERGEINFO,
                               NULL, svn_depth_empty, TRUE, NULL,
                               NULL, NULL /* cancellation */,
                               NULL, NULL /* notification */,
                               scratch_pool));

      if (ctx->notify_func2)
        {
          svn_wc_notify_t *notify;

          notify = svn_wc_create_notify(local_abspath,
                                        svn_wc_notify_merge_elide_info,
                                        scratch_pool);
          ctx->notify_func2(ctx->notify_baton2, notify, scratch_pool);

          notify = svn_wc_create_notify(local_abspath,
                                        svn_wc_notify_update_update,
                                        scratch_pool);
          notify->prop_state = svn_wc_notify_state_changed;

          ctx->notify_func2(ctx->notify_baton2, notify, scratch_pool);
        }
    }

  return SVN_NO_ERROR;
}