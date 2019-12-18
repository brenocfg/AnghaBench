#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* fsap_data; } ;
typedef  TYPE_1__ svn_fs_t ;
typedef  int /*<<< orphan*/  (* svn_fs_pack_notify_t ) (void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  scalar_t__ svn_boolean_t ;
struct pack_baton {scalar_t__ max_mem; void* cancel_baton; int /*<<< orphan*/  cancel_func; void* notify_baton; int /*<<< orphan*/  (* notify_func ) (void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;TYPE_1__* fs; int /*<<< orphan*/  member_0; } ;
struct TYPE_8__ {scalar_t__ format; int max_files_per_dir; int min_unpacked_rev; } ;
typedef  TYPE_2__ fs_fs_data_t ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ DEFAULT_MAX_MEM ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_UNSUPPORTED_FEATURE ; 
 scalar_t__ SVN_FS_FS__MIN_PACKED_FORMAT ; 
 scalar_t__ SVN_FS_FS__MIN_PACK_LOCK_FORMAT ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  get_pack_status (scalar_t__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pack_body ; 
 int /*<<< orphan*/  stub1 (void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_fs__with_pack_lock (TYPE_1__*,int /*<<< orphan*/ ,struct pack_baton*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_fs__with_write_lock (TYPE_1__*,int /*<<< orphan*/ ,struct pack_baton*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_pack_notify_noop ; 

svn_error_t *
svn_fs_fs__pack(svn_fs_t *fs,
                apr_size_t max_mem,
                svn_fs_pack_notify_t notify_func,
                void *notify_baton,
                svn_cancel_func_t cancel_func,
                void *cancel_baton,
                apr_pool_t *pool)
{
  struct pack_baton pb = { 0 };
  fs_fs_data_t *ffd = fs->fsap_data;
  svn_error_t *err;
  svn_boolean_t fully_packed;

  /* If the repository isn't a new enough format, we don't support packing.
     Return a friendly error to that effect. */
  if (ffd->format < SVN_FS_FS__MIN_PACKED_FORMAT)
    return svn_error_createf(SVN_ERR_UNSUPPORTED_FEATURE, NULL,
      _("FSFS format (%d) too old to pack; please upgrade the filesystem."),
      ffd->format);

  /* If we aren't using sharding, we can't do any packing, so quit. */
  if (!ffd->max_files_per_dir)
    {
      if (notify_func)
        (*notify_func)(notify_baton, -1, svn_fs_pack_notify_noop, pool);

      return SVN_NO_ERROR;
    }

  /* Is there we even anything to do?. */
  SVN_ERR(get_pack_status(&fully_packed, fs, pool));
  if (fully_packed)
    {
      if (notify_func)
        (*notify_func)(notify_baton,
                       ffd->min_unpacked_rev / ffd->max_files_per_dir,
                       svn_fs_pack_notify_noop, pool);

      return SVN_NO_ERROR;
    }

  /* Lock the repo and start the pack process. */
  pb.fs = fs;
  pb.notify_func = notify_func;
  pb.notify_baton = notify_baton;
  pb.cancel_func = cancel_func;
  pb.cancel_baton = cancel_baton;
  pb.max_mem = max_mem ? max_mem : DEFAULT_MAX_MEM;

  if (ffd->format >= SVN_FS_FS__MIN_PACK_LOCK_FORMAT)
    {
      /* Newer repositories provide a pack operation specific lock.
         Acquire it to prevent concurrent packs.

         Since the file lock's lifetime is bound to a pool, we create a
         separate subpool here to release the lock immediately after the
         operation finished.
       */
      err = svn_fs_fs__with_pack_lock(fs, pack_body, &pb, pool);
    }
  else
    {
      /* Use the global write lock for older repos. */
      err = svn_fs_fs__with_write_lock(fs, pack_body, &pb, pool);
    }

  return svn_error_trace(err);
}