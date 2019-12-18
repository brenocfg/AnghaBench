#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_lock_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_5__ {scalar_t__ kind; } ;
typedef  TYPE_2__ svn_dirent_t ;
struct print_baton {int /*<<< orphan*/  locks; int /*<<< orphan*/  files; int /*<<< orphan*/  directories; TYPE_1__* ctx; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_4__ {int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  (* cancel_func ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 

__attribute__((used)) static svn_error_t *
print_dirent(void *baton,
             const char *path,
             const svn_dirent_t *dirent,
             const svn_lock_t *lock,
             const char *abs_path,
             const char *external_parent_url,
             const char *external_target,
             apr_pool_t *pool)
{
  struct print_baton *pb = baton;

  if (pb->ctx->cancel_func)
    SVN_ERR(pb->ctx->cancel_func(pb->ctx->cancel_baton));

  if (dirent->kind == svn_node_dir)
    pb->directories++;
  if (dirent->kind == svn_node_file)
    pb->files++;
  if (lock)
    pb->locks++;

  return SVN_NO_ERROR;
}