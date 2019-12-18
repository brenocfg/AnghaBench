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
struct notify_lock_baton_t {int /*<<< orphan*/  inner_baton; int /*<<< orphan*/  (* inner_notify ) (int /*<<< orphan*/ ,TYPE_1__ const*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  had_failure; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc_notify_failed_lock ; 

__attribute__((used)) static void
notify_lock_handler(void *baton,
                    const svn_wc_notify_t *notify,
                    apr_pool_t *scratch_pool)
{
  struct notify_lock_baton_t *nlb = baton;

  if (notify->action == svn_wc_notify_failed_lock)
    nlb->had_failure = TRUE;

  if (nlb->inner_notify)
    nlb->inner_notify(nlb->inner_baton, notify, scratch_pool);
}