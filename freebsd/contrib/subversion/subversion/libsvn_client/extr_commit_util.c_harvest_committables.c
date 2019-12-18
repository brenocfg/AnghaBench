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
typedef  int /*<<< orphan*/  svn_wc_notify_func2_t ;
typedef  int /*<<< orphan*/  svn_wc_context_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int /*<<< orphan*/  svn_client__committables_t ;
typedef  int /*<<< orphan*/  svn_client__check_url_kind_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  scalar_t__ svn_boolean_t ;
struct harvest_baton {char const* root_abspath; char const* commit_relpath; int /*<<< orphan*/ * skip_below_abspath; int /*<<< orphan*/ * result_pool; int /*<<< orphan*/ * wc_ctx; void* notify_baton; int /*<<< orphan*/  notify_func; void* check_url_baton; int /*<<< orphan*/  check_url_func; int /*<<< orphan*/ * danglers; int /*<<< orphan*/ * changelists; scalar_t__ just_locked; int /*<<< orphan*/  depth; int /*<<< orphan*/ * lock_tokens; int /*<<< orphan*/ * committables; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  harvest_status_callback ; 
 int /*<<< orphan*/  svn_wc_walk_status (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct harvest_baton*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
harvest_committables(const char *local_abspath,
                     svn_client__committables_t *committables,
                     apr_hash_t *lock_tokens,
                     const char *copy_mode_relpath,
                     svn_depth_t depth,
                     svn_boolean_t just_locked,
                     apr_hash_t *changelists,
                     apr_hash_t *danglers,
                     svn_client__check_url_kind_t check_url_func,
                     void *check_url_baton,
                     svn_cancel_func_t cancel_func,
                     void *cancel_baton,
                     svn_wc_notify_func2_t notify_func,
                     void *notify_baton,
                     svn_wc_context_t *wc_ctx,
                     apr_pool_t *result_pool,
                     apr_pool_t *scratch_pool)
{
  struct harvest_baton baton;

  SVN_ERR_ASSERT((just_locked && lock_tokens) || !just_locked);

  baton.root_abspath = local_abspath;
  baton.committables = committables;
  baton.lock_tokens = lock_tokens;
  baton.commit_relpath = copy_mode_relpath;
  baton.depth = depth;
  baton.just_locked = just_locked;
  baton.changelists = changelists;
  baton.danglers = danglers;
  baton.check_url_func = check_url_func;
  baton.check_url_baton = check_url_baton;
  baton.notify_func = notify_func;
  baton.notify_baton = notify_baton;
  baton.wc_ctx = wc_ctx;
  baton.result_pool = result_pool;

  baton.skip_below_abspath = NULL;

  SVN_ERR(svn_wc_walk_status(wc_ctx,
                             local_abspath,
                             depth,
                             (copy_mode_relpath != NULL) /* get_all */,
                             FALSE /* no_ignore */,
                             FALSE /* ignore_text_mods */,
                             NULL /* ignore_patterns */,
                             harvest_status_callback,
                             &baton,
                             cancel_func, cancel_baton,
                             scratch_pool));

  return SVN_NO_ERROR;
}