#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc_status3_t ;
typedef  int /*<<< orphan*/  svn_wc_status2_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_3__ {int /*<<< orphan*/ * backwards_compatibility_baton; } ;
typedef  TYPE_1__ svn_client_status_t ;
struct status4_wrapper_baton {int /*<<< orphan*/  old_baton; int /*<<< orphan*/ * (* old_func ) (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  wc_ctx; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_get_absolute (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__status2_from_3 (int /*<<< orphan*/ **,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
status4_wrapper_func(void *baton,
                     const char *path,
                     const svn_client_status_t *status,
                     apr_pool_t *scratch_pool)
{
  struct status4_wrapper_baton *swb = baton;
  svn_wc_status2_t *dup;
  const char *local_abspath;
  const svn_wc_status3_t *wc_status = status->backwards_compatibility_baton;

  SVN_ERR(svn_dirent_get_absolute(&local_abspath, path, scratch_pool));
  SVN_ERR(svn_wc__status2_from_3(&dup, wc_status, swb->wc_ctx,
                                 local_abspath, scratch_pool,
                                 scratch_pool));

  return (*swb->old_func)(swb->old_baton, path, dup, scratch_pool);
}