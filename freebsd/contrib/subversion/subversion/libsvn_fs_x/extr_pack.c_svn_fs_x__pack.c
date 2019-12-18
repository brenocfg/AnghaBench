#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int min_unpacked_rev; int max_files_per_dir; } ;
typedef  TYPE_1__ svn_fs_x__data_t ;
struct TYPE_9__ {TYPE_1__* fsap_data; } ;
typedef  TYPE_2__ svn_fs_t ;
typedef  int /*<<< orphan*/  (* svn_fs_pack_notify_t ) (void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_10__ {scalar_t__ max_mem; void* cancel_baton; int /*<<< orphan*/  cancel_func; void* notify_baton; int /*<<< orphan*/  (* notify_func ) (void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;TYPE_2__* fs; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ pack_baton_t ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ DEFAULT_MAX_MEM ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  get_pack_status (scalar_t__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pack_body ; 
 int /*<<< orphan*/  stub1 (void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_pack_notify_noop ; 
 int /*<<< orphan*/ * svn_fs_x__with_pack_lock (TYPE_2__*,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_x__pack(svn_fs_t *fs,
               apr_size_t max_mem,
               svn_fs_pack_notify_t notify_func,
               void *notify_baton,
               svn_cancel_func_t cancel_func,
               void *cancel_baton,
               apr_pool_t *scratch_pool)
{
  pack_baton_t pb = { 0 };
  svn_boolean_t fully_packed;

  /* Is there we even anything to do?. */
  SVN_ERR(get_pack_status(&fully_packed, fs, scratch_pool));
  if (fully_packed)
    {
      svn_fs_x__data_t *ffd = fs->fsap_data;

      if (notify_func)
        (*notify_func)(notify_baton,
                       ffd->min_unpacked_rev / ffd->max_files_per_dir,
                       svn_fs_pack_notify_noop, scratch_pool);

      return SVN_NO_ERROR;
    }

  /* Lock the repo and start the pack process. */
  pb.fs = fs;
  pb.notify_func = notify_func;
  pb.notify_baton = notify_baton;
  pb.cancel_func = cancel_func;
  pb.cancel_baton = cancel_baton;
  pb.max_mem = max_mem ? max_mem : DEFAULT_MAX_MEM;

  return svn_fs_x__with_pack_lock(fs, pack_body, &pb, scratch_pool);
}