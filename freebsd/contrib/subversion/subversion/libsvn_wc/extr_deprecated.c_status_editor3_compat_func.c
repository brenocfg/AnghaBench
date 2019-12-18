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
typedef  int /*<<< orphan*/  svn_wc_status2_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct status_editor3_compat_baton {int /*<<< orphan*/  old_baton; int /*<<< orphan*/  (* old_func ) (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
status_editor3_compat_func(void *baton,
                           const char *path,
                           svn_wc_status2_t *status,
                           apr_pool_t *pool)
{
  struct status_editor3_compat_baton *secb = baton;

  secb->old_func(secb->old_baton, path, status);
  return SVN_NO_ERROR;
}