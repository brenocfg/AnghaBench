#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stringbuf_t ;
typedef  scalar_t__ svn_revnum_t ;
struct TYPE_11__ {int max_files_per_dir; } ;
typedef  TYPE_1__ svn_fs_x__data_t ;
struct TYPE_12__ {TYPE_1__* fsap_data; } ;
typedef  TYPE_2__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_15__ {scalar_t__ start_rev; } ;
struct TYPE_13__ {int revision; TYPE_5__* manifest; TYPE_9__ entry; int /*<<< orphan*/  folder; } ;
typedef  TYPE_3__ packed_revprops_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_14__ {int nelts; } ;

/* Variables and functions */
 TYPE_9__ APR_ARRAY_IDX (TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PATH_MANIFEST ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_CORRUPT_REVPROP_MANIFEST ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int get_entry (TYPE_5__*,int) ; 
 int /*<<< orphan*/  manifest_entry_t ; 
 int /*<<< orphan*/  read_manifest (TYPE_5__**,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_dirent_join (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  svn_fs_x__path_pack_shard (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__read_content (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_revprop_packname(svn_fs_t *fs,
                     packed_revprops_t *revprops,
                     apr_pool_t *result_pool,
                     apr_pool_t *scratch_pool)
{
  svn_fs_x__data_t *ffd = fs->fsap_data;
  svn_stringbuf_t *content = NULL;
  const char *manifest_file_path;
  int idx;
  svn_revnum_t previous_start_rev;
  int i;

  /* Determine the dimensions. Rev 0 is excluded from the first shard. */
  int rev_count = ffd->max_files_per_dir;
  svn_revnum_t manifest_start
    = revprops->revision - (revprops->revision % rev_count);
  if (manifest_start == 0)
    {
      ++manifest_start;
      --rev_count;
    }

  /* Read the content of the manifest file */
  revprops->folder = svn_fs_x__path_pack_shard(fs, revprops->revision,
                                               result_pool);
  manifest_file_path = svn_dirent_join(revprops->folder, PATH_MANIFEST,
                                       result_pool);
  SVN_ERR(svn_fs_x__read_content(&content, manifest_file_path, result_pool));
  SVN_ERR(read_manifest(&revprops->manifest, content, revprops->revision,
                        result_pool, scratch_pool));

  /* Verify the manifest data. */
  if (revprops->manifest->nelts == 0)
    return svn_error_createf(SVN_ERR_FS_CORRUPT_REVPROP_MANIFEST, NULL,
                             "Revprop manifest for r%ld is empty",
                             revprops->revision);

  previous_start_rev = 0;
  for (i = 0; i < revprops->manifest->nelts; ++i)
    {
      svn_revnum_t start_rev = APR_ARRAY_IDX(revprops->manifest, i,
                                             manifest_entry_t).start_rev;
      if (   start_rev < manifest_start
          || start_rev >= manifest_start + rev_count)
        return svn_error_createf(SVN_ERR_FS_CORRUPT_REVPROP_MANIFEST, NULL,
                                 "Revprop manifest for r%ld contains "
                                 "out-of-range revision r%ld",
                                 revprops->revision, start_rev);

      if (start_rev < previous_start_rev)
        return svn_error_createf(SVN_ERR_FS_CORRUPT_REVPROP_MANIFEST, NULL,
                                 "Entries in revprop manifest for r%ld "
                                 "are not ordered", revprops->revision);

      previous_start_rev = start_rev;
    }

  /* Now get the pack file description */
  idx = get_entry(revprops->manifest, revprops->revision);
  revprops->entry = APR_ARRAY_IDX(revprops->manifest, idx,
                                  manifest_entry_t);

  return SVN_NO_ERROR;
}