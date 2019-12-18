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
struct TYPE_3__ {scalar_t__ action; } ;
typedef  TYPE_1__ svn_repos_notify_t ;
struct recover_baton {int /*<<< orphan*/  start_callback_baton; int /*<<< orphan*/  (* start_callback ) (int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ ) ; 
 scalar_t__ svn_repos_notify_mutex_acquired ; 

__attribute__((used)) static void
recovery_started(void *baton,
                 const svn_repos_notify_t *notify,
                 apr_pool_t *scratch_pool)
{
  struct recover_baton *rb = baton;

  if (notify->action == svn_repos_notify_mutex_acquired
      && rb->start_callback != NULL)
    svn_error_clear(rb->start_callback(rb->start_callback_baton));
}