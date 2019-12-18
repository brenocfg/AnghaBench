#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ action; } ;
typedef  TYPE_1__ svn_wc_notify_t ;
struct downgrade_commit_copied_notify_baton {int /*<<< orphan*/  orig_notify_baton2; int /*<<< orphan*/  (* orig_notify_func2 ) (int /*<<< orphan*/ ,TYPE_1__ const*,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc_dup_notify (TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc_notify_commit_added ; 
 scalar_t__ svn_wc_notify_commit_copied ; 
 scalar_t__ svn_wc_notify_commit_copied_replaced ; 
 scalar_t__ svn_wc_notify_commit_replaced ; 

__attribute__((used)) static void
downgrade_commit_copied_notify_func(void *baton,
                                    const svn_wc_notify_t *notify,
                                    apr_pool_t *pool)
{
  struct downgrade_commit_copied_notify_baton *b = baton;

  if (notify->action == svn_wc_notify_commit_copied)
    {
      svn_wc_notify_t *my_notify = svn_wc_dup_notify(notify, pool);
      my_notify->action = svn_wc_notify_commit_added;
      notify = my_notify;
    }
  else if (notify->action == svn_wc_notify_commit_copied_replaced)
    {
      svn_wc_notify_t *my_notify = svn_wc_dup_notify(notify, pool);
      my_notify->action = svn_wc_notify_commit_replaced;
      notify = my_notify;
    }

  /* Call the wrapped notification system (if any) with MY_NOTIFY,
     which is either the original NOTIFY object, or a tweaked deep
     copy thereof. */
  if (b->orig_notify_func2)
    b->orig_notify_func2(b->orig_notify_baton2, notify, pool);
}