#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct pack_baton {int shard; int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  (* cancel_func ) (int /*<<< orphan*/ ) ;TYPE_2__* fs; void* revsprops_dir; void* revs_dir; int /*<<< orphan*/  notify_baton; int /*<<< orphan*/  (* notify_func ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_3__ {int min_unpacked_rev; int max_files_per_dir; int youngest_rev_cache; scalar_t__ format; } ;
typedef  TYPE_1__ fs_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int apr_int64_t ;
struct TYPE_4__ {int /*<<< orphan*/  path; TYPE_1__* fsap_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  PATH_REVPROPS_DIR ; 
 int /*<<< orphan*/  PATH_REVS_DIR ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_FS_FS__MIN_PACKED_REVPROP_FORMAT ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  get_pack_status (scalar_t__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pack_shard (struct pack_baton*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 void* svn_dirent_join (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_pack_notify_noop ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
pack_body(void *baton,
          apr_pool_t *pool)
{
  struct pack_baton *pb = baton;
  fs_fs_data_t *ffd = pb->fs->fsap_data;
  apr_int64_t completed_shards;
  apr_pool_t *iterpool;
  svn_boolean_t fully_packed;

  /* Since another process might have already packed the repo,
     we need to re-read the pack status. */
  SVN_ERR(get_pack_status(&fully_packed, pb->fs, pool));
  if (fully_packed)
    {
      if (pb->notify_func)
        (*pb->notify_func)(pb->notify_baton,
                           ffd->min_unpacked_rev / ffd->max_files_per_dir,
                           svn_fs_pack_notify_noop, pool);

      return SVN_NO_ERROR;
    }

  completed_shards = (ffd->youngest_rev_cache + 1) / ffd->max_files_per_dir;
  pb->revs_dir = svn_dirent_join(pb->fs->path, PATH_REVS_DIR, pool);
  if (ffd->format >= SVN_FS_FS__MIN_PACKED_REVPROP_FORMAT)
    pb->revsprops_dir = svn_dirent_join(pb->fs->path, PATH_REVPROPS_DIR,
                                        pool);

  iterpool = svn_pool_create(pool);
  for (pb->shard = ffd->min_unpacked_rev / ffd->max_files_per_dir;
       pb->shard < completed_shards;
       pb->shard++)
    {
      svn_pool_clear(iterpool);

      if (pb->cancel_func)
        SVN_ERR(pb->cancel_func(pb->cancel_baton));

      SVN_ERR(pack_shard(pb, iterpool));
    }

  svn_pool_destroy(iterpool);
  return SVN_NO_ERROR;
}