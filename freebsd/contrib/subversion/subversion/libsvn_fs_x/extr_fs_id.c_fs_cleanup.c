#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  owner; TYPE_1__* fs; int /*<<< orphan*/  svn_fs_open_; int /*<<< orphan*/  fs_path; } ;
typedef  TYPE_2__ svn_fs_x__id_context_t ;
struct TYPE_7__ {int /*<<< orphan*/  svn_fs_open_; } ;
typedef  TYPE_3__ svn_fs_x__data_t ;
typedef  int /*<<< orphan*/  apr_status_t ;
struct TYPE_5__ {int /*<<< orphan*/  path; TYPE_3__* fsap_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 
 int /*<<< orphan*/  apr_pool_cleanup_kill (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  owner_cleanup ; 

__attribute__((used)) static apr_status_t
fs_cleanup(void *baton)
{
  svn_fs_x__id_context_t *context = baton;
  svn_fs_x__data_t *ffd = context->fs->fsap_data;

  /* Remember the FS_PATH to potentially reopen and mark the FS as n/a. */
  context->fs_path = apr_pstrdup(context->owner, context->fs->path);
  context->svn_fs_open_ = ffd->svn_fs_open_;
  context->fs = NULL;


  /* No need for further notifications because from now on, everything is
     allocated in OWNER. */
  apr_pool_cleanup_kill(context->owner, context, owner_cleanup);

  return  APR_SUCCESS;
}