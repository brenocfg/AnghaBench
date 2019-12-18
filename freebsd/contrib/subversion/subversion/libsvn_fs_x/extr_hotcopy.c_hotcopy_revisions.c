#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_revnum_t ;
struct TYPE_10__ {int max_files_per_dir; } ;
typedef  TYPE_1__ svn_fs_x__data_t ;
struct TYPE_11__ {int /*<<< orphan*/  path; TYPE_1__* fsap_data; } ;
typedef  TYPE_2__ svn_fs_t ;
typedef  int /*<<< orphan*/  (* svn_fs_hotcopy_notify_t ) (void*,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  (* svn_cancel_func_t ) (void*) ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PATH_MIN_UNPACKED_REV ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/  SVN_ERR_UNSUPPORTED_FEATURE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  hotcopy_copy_packed_shard (int /*<<< orphan*/ *,scalar_t__*,TYPE_2__*,TYPE_2__*,scalar_t__,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hotcopy_copy_shard_file (int /*<<< orphan*/ *,char const*,char const*,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  svn_fs_x__path_shard (TYPE_2__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__read_min_unpacked_rev (scalar_t__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__write_current (TYPE_2__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_dir_file_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_remove_dir2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (void*),void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
hotcopy_revisions(svn_fs_t *src_fs,
                  svn_fs_t *dst_fs,
                  svn_revnum_t src_youngest,
                  svn_revnum_t dst_youngest,
                  svn_boolean_t incremental,
                  const char *src_revs_dir,
                  const char *dst_revs_dir,
                  svn_fs_hotcopy_notify_t notify_func,
                  void* notify_baton,
                  svn_cancel_func_t cancel_func,
                  void* cancel_baton,
                  apr_pool_t *scratch_pool)
{
  svn_fs_x__data_t *src_ffd = src_fs->fsap_data;
  int max_files_per_dir = src_ffd->max_files_per_dir;
  svn_revnum_t src_min_unpacked_rev;
  svn_revnum_t dst_min_unpacked_rev;
  svn_revnum_t rev;
  apr_pool_t *iterpool;

  /* Copy the min unpacked rev, and read its value. */
  SVN_ERR(svn_fs_x__read_min_unpacked_rev(&src_min_unpacked_rev, src_fs,
                                          scratch_pool));
  SVN_ERR(svn_fs_x__read_min_unpacked_rev(&dst_min_unpacked_rev, dst_fs,
                                          scratch_pool));

  /* We only support packs coming from the hotcopy source.
    * The destination should not be packed independently from
    * the source. This also catches the case where users accidentally
    * swap the source and destination arguments. */
  if (src_min_unpacked_rev < dst_min_unpacked_rev)
    return svn_error_createf(SVN_ERR_UNSUPPORTED_FEATURE, NULL,
                             _("The hotcopy destination already contains "
                               "more packed revisions (%lu) than the "
                               "hotcopy source contains (%lu)"),
                             dst_min_unpacked_rev - 1,
                             src_min_unpacked_rev - 1);

  SVN_ERR(svn_io_dir_file_copy(src_fs->path, dst_fs->path,
                               PATH_MIN_UNPACKED_REV, scratch_pool));

  if (cancel_func)
    SVN_ERR(cancel_func(cancel_baton));

  /*
   * Copy the necessary rev files.
   */

  iterpool = svn_pool_create(scratch_pool);
  /* First, copy packed shards. */
  for (rev = 0; rev < src_min_unpacked_rev; rev += max_files_per_dir)
    {
      svn_boolean_t skipped = TRUE;
      svn_revnum_t pack_end_rev;

      svn_pool_clear(iterpool);

      if (cancel_func)
        SVN_ERR(cancel_func(cancel_baton));

      /* Copy the packed shard. */
      SVN_ERR(hotcopy_copy_packed_shard(&skipped, &dst_min_unpacked_rev,
                                        src_fs, dst_fs,
                                        rev, max_files_per_dir,
                                        iterpool));

      pack_end_rev = rev + max_files_per_dir - 1;

      /* Whenever this pack did not previously exist in the destination,
       * update 'current' to the most recent packed rev (so readers can see
       * new revisions which arrived in this pack). */
      if (pack_end_rev > dst_youngest)
        {
          SVN_ERR(svn_fs_x__write_current(dst_fs, pack_end_rev, iterpool));
        }

      /* When notifying about packed shards, make things simpler by either
       * reporting a full revision range, i.e [pack start, pack end] or
       * reporting nothing. There is one case when this approach might not
       * be exact (incremental hotcopy with a pack replacing last unpacked
       * revisions), but generally this is good enough. */
      if (notify_func && !skipped)
        notify_func(notify_baton, rev, pack_end_rev, iterpool);

      /* Now that all revisions have moved into the pack, the original
       * rev dir can be removed. */
      SVN_ERR(svn_io_remove_dir2(svn_fs_x__path_shard(dst_fs, rev, iterpool),
                                 TRUE, cancel_func, cancel_baton, iterpool));
    }

  if (cancel_func)
    SVN_ERR(cancel_func(cancel_baton));

  SVN_ERR_ASSERT(rev == src_min_unpacked_rev);
  SVN_ERR_ASSERT(src_min_unpacked_rev == dst_min_unpacked_rev);

  /* Now, copy pairs of non-packed revisions and revprop files.
   * If necessary, update 'current' after copying all files from a shard. */
  for (; rev <= src_youngest; rev++)
    {
      svn_boolean_t skipped = TRUE;

      svn_pool_clear(iterpool);

      if (cancel_func)
        SVN_ERR(cancel_func(cancel_baton));

      /* Copying non-packed revisions is racy in case the source repository is
       * being packed concurrently with this hotcopy operation.  With the pack
       * lock, however, the race is impossible, because hotcopy and pack
       * operations block each other.
       *
       * We assume that all revisions coming after 'min-unpacked-rev' really
       * are unpacked and that's not necessarily true with concurrent packing.
       * Don't try to be smart in this edge case, because handling it properly
       * might require copying *everything* from the start. Just abort the
       * hotcopy with an ENOENT (revision file moved to a pack, so it is no
       * longer where we expect it to be). */

      /* Copy the rev file. */
      SVN_ERR(hotcopy_copy_shard_file(&skipped, src_revs_dir, dst_revs_dir,
                                      rev, max_files_per_dir, FALSE,
                                      iterpool));

      /* Copy the revprop file. */
      SVN_ERR(hotcopy_copy_shard_file(&skipped, src_revs_dir, dst_revs_dir,
                                      rev, max_files_per_dir, TRUE,
                                      iterpool));

      /* Whenever this revision did not previously exist in the destination,
       * checkpoint the progress via 'current' (do that once per full shard
       * in order not to slow things down). */
      if (rev > dst_youngest)
        {
          if (max_files_per_dir && (rev % max_files_per_dir == 0))
            {
              SVN_ERR(svn_fs_x__write_current(dst_fs, rev, iterpool));
            }
        }

      if (notify_func && !skipped)
        notify_func(notify_baton, rev, rev, iterpool);
    }
  svn_pool_destroy(iterpool);

  /* We assume that all revisions were copied now, i.e. we didn't exit the
   * above loop early. 'rev' was last incremented during exit of the loop. */
  SVN_ERR_ASSERT(rev == src_youngest + 1);

  return SVN_NO_ERROR;
}