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
struct TYPE_4__ {int /*<<< orphan*/  action; void* revision; void* shard; } ;
typedef  TYPE_1__ svn_repos_notify_t ;
typedef  int svn_fs_upgrade_notify_action_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct fs_upgrade_notify_baton_t {int /*<<< orphan*/  notify_baton; int /*<<< orphan*/  (* notify_func ) (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ;} ;
typedef  void* apr_uint64_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_MALFUNCTION () ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
#define  svn_fs_upgrade_cleanup_revprops 130 
#define  svn_fs_upgrade_format_bumped 129 
#define  svn_fs_upgrade_pack_revprops 128 
 int /*<<< orphan*/  svn_repos_notify_cleanup_revprops ; 
 TYPE_1__* svn_repos_notify_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos_notify_format_bumped ; 
 int /*<<< orphan*/  svn_repos_notify_mutex_acquired ; 
 int /*<<< orphan*/  svn_repos_notify_pack_revprops ; 

__attribute__((used)) static svn_error_t *
fs_upgrade_notify(void *baton,
                  apr_uint64_t number,
                  svn_fs_upgrade_notify_action_t action,
                  apr_pool_t *pool)
{
  struct fs_upgrade_notify_baton_t *fs_baton = baton;

  svn_repos_notify_t *notify = svn_repos_notify_create(
                                svn_repos_notify_mutex_acquired, pool);
  switch(action)
    {
      case svn_fs_upgrade_pack_revprops:
        notify->shard = number;
        notify->action = svn_repos_notify_pack_revprops;
        break;

      case svn_fs_upgrade_cleanup_revprops:
        notify->shard = number;
        notify->action = svn_repos_notify_cleanup_revprops;
        break;

      case svn_fs_upgrade_format_bumped:
        notify->revision = number;
        notify->action = svn_repos_notify_format_bumped;
        break;

      default:
        /* unknown notification */
        SVN_ERR_MALFUNCTION();
    }

  fs_baton->notify_func(fs_baton->notify_baton, notify, pool);

  return SVN_NO_ERROR;
}