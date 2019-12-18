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
struct TYPE_3__ {int /*<<< orphan*/  db_path; } ;
typedef  TYPE_1__ svn_repos_t ;
typedef  scalar_t__ svn_repos_notify_func_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
struct pack_notify_baton {void* notify_baton; scalar_t__ notify_func; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * pack_notify_func ; 
 int /*<<< orphan*/ * svn_fs_pack (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pack_notify_baton*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_repos_fs_pack2(svn_repos_t *repos,
                   svn_repos_notify_func_t notify_func,
                   void *notify_baton,
                   svn_cancel_func_t cancel_func,
                   void *cancel_baton,
                   apr_pool_t *pool)
{
  struct pack_notify_baton pnb;

  pnb.notify_func = notify_func;
  pnb.notify_baton = notify_baton;

  return svn_fs_pack(repos->db_path,
                     notify_func ? pack_notify_func : NULL,
                     notify_func ? &pnb : NULL,
                     cancel_func, cancel_baton, pool);
}