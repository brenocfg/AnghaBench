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
typedef  int /*<<< orphan*/  svn_repos_t ;
typedef  int /*<<< orphan*/  svn_fs_pack_notify_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
struct pack_notify_wrapper_baton {void* notify_baton; int /*<<< orphan*/  notify_func; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  pack_notify_wrapper_func ; 
 int /*<<< orphan*/ * svn_repos_fs_pack2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct pack_notify_wrapper_baton*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_repos_fs_pack(svn_repos_t *repos,
                  svn_fs_pack_notify_t notify_func,
                  void *notify_baton,
                  svn_cancel_func_t cancel_func,
                  void *cancel_baton,
                  apr_pool_t *pool)
{
  struct pack_notify_wrapper_baton pnwb;

  pnwb.notify_func = notify_func;
  pnwb.notify_baton = notify_baton;

  return svn_repos_fs_pack2(repos, pack_notify_wrapper_func, &pnwb,
                            cancel_func, cancel_baton, pool);
}