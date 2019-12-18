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
struct TYPE_5__ {int min_unpacked_rev; int max_files_per_dir; int youngest_rev_cache; scalar_t__ compress_packed_revprops; int /*<<< orphan*/  revprop_pack_size; } ;
typedef  TYPE_1__ svn_fs_x__data_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_6__ {int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  (* cancel_func ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  notify_baton; int /*<<< orphan*/  (* notify_func ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  max_mem; TYPE_3__* fs; } ;
typedef  TYPE_2__ pack_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int apr_int64_t ;
struct TYPE_7__ {int /*<<< orphan*/  path; TYPE_1__* fsap_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  PATH_REVS_DIR ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN__COMPRESSION_NONE ; 
 int /*<<< orphan*/  SVN__COMPRESSION_ZLIB_DEFAULT ; 
 int /*<<< orphan*/  get_pack_status (scalar_t__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pack_shard (char const*,TYPE_3__*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *),int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ),int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 char* svn_dirent_join (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_pack_notify_noop ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
pack_body(void *baton,
          apr_pool_t *scratch_pool)
{
  pack_baton_t *pb = baton;
  svn_fs_x__data_t *ffd = pb->fs->fsap_data;
  apr_int64_t completed_shards;
  apr_int64_t i;
  apr_pool_t *iterpool;
  const char *data_path;
  svn_boolean_t fully_packed;

  /* Since another process might have already packed the repo,
     we need to re-read the pack status. */
  SVN_ERR(get_pack_status(&fully_packed, pb->fs, scratch_pool));
  if (fully_packed)
    {
      if (pb->notify_func)
        (*pb->notify_func)(pb->notify_baton,
                           ffd->min_unpacked_rev / ffd->max_files_per_dir,
                           svn_fs_pack_notify_noop, scratch_pool);

      return SVN_NO_ERROR;
    }

  completed_shards = (ffd->youngest_rev_cache + 1) / ffd->max_files_per_dir;
  data_path = svn_dirent_join(pb->fs->path, PATH_REVS_DIR, scratch_pool);

  iterpool = svn_pool_create(scratch_pool);
  for (i = ffd->min_unpacked_rev / ffd->max_files_per_dir;
       i < completed_shards;
       i++)
    {
      svn_pool_clear(iterpool);

      if (pb->cancel_func)
        SVN_ERR(pb->cancel_func(pb->cancel_baton));

      SVN_ERR(pack_shard(data_path,
                         pb->fs, i, ffd->max_files_per_dir,
                         ffd->revprop_pack_size,
                         ffd->compress_packed_revprops
                           ? SVN__COMPRESSION_ZLIB_DEFAULT
                           : SVN__COMPRESSION_NONE,
                         pb->max_mem,
                         pb->notify_func, pb->notify_baton,
                         pb->cancel_func, pb->cancel_baton, iterpool));
    }

  svn_pool_destroy(iterpool);
  return SVN_NO_ERROR;
}