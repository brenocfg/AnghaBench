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
struct TYPE_4__ {int /*<<< orphan*/  shard; } ;
typedef  TYPE_1__ svn_repos_notify_t ;
typedef  scalar_t__ svn_repos_notify_action_t ;
typedef  scalar_t__ svn_fs_pack_notify_action_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct pack_notify_baton {int /*<<< orphan*/  notify_baton; int /*<<< orphan*/  (* notify_func ) (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_pack_notify_noop ; 
 scalar_t__ svn_fs_pack_notify_start ; 
 TYPE_1__* svn_repos_notify_create (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_repos_notify_pack_noop ; 
 scalar_t__ svn_repos_notify_pack_shard_start ; 

__attribute__((used)) static svn_error_t *
pack_notify_func(void *baton,
                 apr_int64_t shard,
                 svn_fs_pack_notify_action_t pack_action,
                 apr_pool_t *pool)
{
  struct pack_notify_baton *pnb = baton;
  svn_repos_notify_t *notify;
  svn_repos_notify_action_t repos_action;

  /* Simple conversion works for these values. */
  SVN_ERR_ASSERT(pack_action >= svn_fs_pack_notify_start
                 && pack_action <= svn_fs_pack_notify_noop);

  repos_action = pack_action == svn_fs_pack_notify_noop
               ? svn_repos_notify_pack_noop
               : pack_action + svn_repos_notify_pack_shard_start
                             - svn_fs_pack_notify_start;

  notify = svn_repos_notify_create(repos_action, pool);
  notify->shard = shard;
  pnb->notify_func(pnb->notify_baton, notify, pool);

  return SVN_NO_ERROR;
}