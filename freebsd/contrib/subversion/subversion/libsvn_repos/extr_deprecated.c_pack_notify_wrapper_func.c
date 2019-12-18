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
struct TYPE_3__ {scalar_t__ action; int /*<<< orphan*/  shard; } ;
typedef  TYPE_1__ svn_repos_notify_t ;
struct pack_notify_wrapper_baton {int /*<<< orphan*/  notify_baton; int /*<<< orphan*/  (* notify_func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pack_notify_wrapper_func(void *baton,
                         const svn_repos_notify_t *notify,
                         apr_pool_t *scratch_pool)
{
  struct pack_notify_wrapper_baton *pnwb = baton;

  svn_error_clear(pnwb->notify_func(pnwb->notify_baton, notify->shard,
                                    notify->action - 3, scratch_pool));
}