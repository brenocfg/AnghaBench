#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ action; } ;
typedef  TYPE_1__ svn_wc_notify_t ;
struct svn_cl__check_externals_failed_notify_baton {int /*<<< orphan*/  wrapped_baton; int /*<<< orphan*/  (* wrapped_func ) (int /*<<< orphan*/ ,TYPE_1__ const*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  had_externals_error; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc_notify_failed_external ; 

void
svn_cl__check_externals_failed_notify_wrapper(void *baton,
                                              const svn_wc_notify_t *n,
                                              apr_pool_t *pool)
{
  struct svn_cl__check_externals_failed_notify_baton *nwb = baton;

  if (n->action == svn_wc_notify_failed_external)
    nwb->had_externals_error = TRUE;

  if (nwb->wrapped_func)
    nwb->wrapped_func(nwb->wrapped_baton, n, pool);
}