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
typedef  void* svn_revnum_t ;
struct TYPE_4__ {void* end_revision; void* start_revision; } ;
typedef  TYPE_1__ svn_repos_notify_t ;
struct fs_hotcopy_notify_baton_t {int /*<<< orphan*/  notify_baton; int /*<<< orphan*/  (* notify_func ) (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_repos_notify_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos_notify_hotcopy_rev_range ; 

__attribute__((used)) static void
fs_hotcopy_notify(void *baton,
                  svn_revnum_t start_revision,
                  svn_revnum_t end_revision,
                  apr_pool_t *pool)
{
  struct fs_hotcopy_notify_baton_t *fs_baton = baton;
  svn_repos_notify_t *notify;

  notify = svn_repos_notify_create(svn_repos_notify_hotcopy_rev_range, pool);
  notify->start_revision = start_revision;
  notify->end_revision = end_revision;

  fs_baton->notify_func(fs_baton->notify_baton, notify, pool);
}