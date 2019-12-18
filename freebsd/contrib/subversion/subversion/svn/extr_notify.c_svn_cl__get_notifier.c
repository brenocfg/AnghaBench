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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cl__conflict_stats_t ;
struct notify_baton {int /*<<< orphan*/  path_prefix; int /*<<< orphan*/ * conflict_stats; void* had_print_error; scalar_t__ progress_revision; scalar_t__ in_external; void* is_wc_to_repos_copy; void* is_export; void* is_checkout; void* sent_first_txdelta; void* received_some_change; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 struct notify_baton* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  notify ; 
 int /*<<< orphan*/  svn_dirent_get_absolute (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_cl__get_notifier(svn_wc_notify_func2_t *notify_func_p,
                     void **notify_baton_p,
                     svn_cl__conflict_stats_t *conflict_stats,
                     apr_pool_t *pool)
{
  struct notify_baton *nb = apr_pcalloc(pool, sizeof(*nb));

  nb->received_some_change = FALSE;
  nb->sent_first_txdelta = FALSE;
  nb->is_checkout = FALSE;
  nb->is_export = FALSE;
  nb->is_wc_to_repos_copy = FALSE;
  nb->in_external = 0;
  nb->progress_revision = 0;
  nb->had_print_error = FALSE;
  nb->conflict_stats = conflict_stats;
  SVN_ERR(svn_dirent_get_absolute(&nb->path_prefix, "", pool));

  *notify_func_p = notify;
  *notify_baton_p = nb;
  return SVN_NO_ERROR;
}