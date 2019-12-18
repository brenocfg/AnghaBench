#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_revnum_t ;
typedef  scalar_t__ svn_node_kind_t ;
struct TYPE_11__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_hotcopy_notify_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  (* svn_cancel_func_t ) (void*) ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_12__ {void* cancel_baton; int /*<<< orphan*/  (* cancel_func ) (void*) ;void* notify_baton; int /*<<< orphan*/  notify_func; scalar_t__ incremental; TYPE_1__* dst_fs; TYPE_1__* src_fs; } ;
typedef  TYPE_2__ hotcopy_body_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PATH_CONFIG ; 
 int /*<<< orphan*/  PATH_LOCKS_DIR ; 
 int /*<<< orphan*/  PATH_REVS_DIR ; 
 int /*<<< orphan*/  PATH_TXN_CURRENT ; 
 int /*<<< orphan*/  REP_CACHE_DB_NAME ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_UNSUPPORTED_FEATURE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  hotcopy_revisions (TYPE_1__*,TYPE_1__*,scalar_t__,scalar_t__,scalar_t__,char const*,char const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/  (*) (void*),void*,int /*<<< orphan*/ *) ; 
 char* svn_dirent_join (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  svn_fs_x__del_rep_reference (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__read_current (scalar_t__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__reset_revprop_generation_file (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__write_current (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__write_format (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__youngest_rev (scalar_t__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_check_path (char const*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_copy_dir_recursively (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (void*),void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_dir_file_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_make_dir_recursively (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_remove_dir2 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (void*),void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_set_file_read_write (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 int /*<<< orphan*/  svn_sqlite__hotcopy (char const*,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
hotcopy_body(void *baton,
             apr_pool_t *scratch_pool)
{
  hotcopy_body_baton_t *hbb = baton;
  svn_fs_t *src_fs = hbb->src_fs;
  svn_fs_t *dst_fs = hbb->dst_fs;
  svn_boolean_t incremental = hbb->incremental;
  svn_fs_hotcopy_notify_t notify_func = hbb->notify_func;
  void* notify_baton = hbb->notify_baton;
  svn_cancel_func_t cancel_func = hbb->cancel_func;
  void* cancel_baton = hbb->cancel_baton;
  svn_revnum_t src_youngest;
  svn_revnum_t dst_youngest;
  const char *src_revs_dir;
  const char *dst_revs_dir;
  const char *src_subdir;
  const char *dst_subdir;
  svn_node_kind_t kind;

  /* Try to copy the config.
   *
   * ### We try copying the config file before doing anything else,
   * ### because higher layers will abort the hotcopy if we throw
   * ### an error from this function, and that renders the hotcopy
   * ### unusable anyway. */
  SVN_ERR(svn_io_dir_file_copy(src_fs->path, dst_fs->path, PATH_CONFIG,
                               scratch_pool));

  if (cancel_func)
    SVN_ERR(cancel_func(cancel_baton));

  /* Find the youngest revision in the source and destination.
   * We only support hotcopies from sources with an equal or greater amount
   * of revisions than the destination.
   * This also catches the case where users accidentally swap the
   * source and destination arguments. */
  SVN_ERR(svn_fs_x__read_current(&src_youngest, src_fs, scratch_pool));
  if (incremental)
    {
      SVN_ERR(svn_fs_x__youngest_rev(&dst_youngest, dst_fs, scratch_pool));
      if (src_youngest < dst_youngest)
        return svn_error_createf(SVN_ERR_UNSUPPORTED_FEATURE, NULL,
                 _("The hotcopy destination already contains more revisions "
                   "(%lu) than the hotcopy source contains (%lu); are source "
                   "and destination swapped?"),
                   dst_youngest, src_youngest);
    }
  else
    dst_youngest = 0;

  src_revs_dir = svn_dirent_join(src_fs->path, PATH_REVS_DIR, scratch_pool);
  dst_revs_dir = svn_dirent_join(dst_fs->path, PATH_REVS_DIR, scratch_pool);

  /* Ensure that the required folders exist in the destination
   * before actually copying the revisions and revprops. */
  SVN_ERR(svn_io_make_dir_recursively(dst_revs_dir, scratch_pool));
  if (cancel_func)
    SVN_ERR(cancel_func(cancel_baton));

  /* Split the logic for new and old FS formats. The latter is much simpler
   * due to the absense of sharding and packing. However, it requires special
   * care when updating the 'current' file (which contains not just the
   * revision number, but also the next-ID counters). */
  SVN_ERR(hotcopy_revisions(src_fs, dst_fs, src_youngest, dst_youngest,
                            incremental, src_revs_dir, dst_revs_dir,
                            notify_func, notify_baton,
                            cancel_func, cancel_baton, scratch_pool));
  SVN_ERR(svn_fs_x__write_current(dst_fs, src_youngest, scratch_pool));

  /* Replace the locks tree.
   * This is racy in case readers are currently trying to list locks in
   * the destination. However, we need to get rid of stale locks.
   * This is the simplest way of doing this, so we accept this small race. */
  dst_subdir = svn_dirent_join(dst_fs->path, PATH_LOCKS_DIR, scratch_pool);
  SVN_ERR(svn_io_remove_dir2(dst_subdir, TRUE, cancel_func, cancel_baton,
                             scratch_pool));
  src_subdir = svn_dirent_join(src_fs->path, PATH_LOCKS_DIR, scratch_pool);
  SVN_ERR(svn_io_check_path(src_subdir, &kind, scratch_pool));
  if (kind == svn_node_dir)
    SVN_ERR(svn_io_copy_dir_recursively(src_subdir, dst_fs->path,
                                        PATH_LOCKS_DIR, TRUE,
                                        cancel_func, cancel_baton,
                                        scratch_pool));

  /*
   * NB: Data copied below is only read by writers, not readers.
   *     Writers are still locked out at this point.
   */

  /* Copy the rep cache and then remove entries for revisions
   * younger than the destination's youngest revision. */
  src_subdir = svn_dirent_join(src_fs->path, REP_CACHE_DB_NAME, scratch_pool);
  dst_subdir = svn_dirent_join(dst_fs->path, REP_CACHE_DB_NAME, scratch_pool);
  SVN_ERR(svn_io_check_path(src_subdir, &kind, scratch_pool));
  if (kind == svn_node_file)
    {
      /* Copy the rep cache and then remove entries for revisions
       * that did not make it into the destination. */
      SVN_ERR(svn_sqlite__hotcopy(src_subdir, dst_subdir, scratch_pool));

      /* The source might have r/o flags set on it - which would be
         carried over to the copy. */
      SVN_ERR(svn_io_set_file_read_write(dst_subdir, FALSE, scratch_pool));
      SVN_ERR(svn_fs_x__del_rep_reference(dst_fs, src_youngest,
                                          scratch_pool));
    }

  /* Copy the txn-current file. */
  SVN_ERR(svn_io_dir_file_copy(src_fs->path, dst_fs->path,
                                PATH_TXN_CURRENT, scratch_pool));

  /* If a revprop generation file exists in the source filesystem,
   * reset it to zero (since this is on a different path, it will not
   * overlap with data already in cache).  Also, clean up stale files
   * used for the named atomics implementation. */
  SVN_ERR(svn_fs_x__reset_revprop_generation_file(dst_fs, scratch_pool));

  /* Hotcopied FS is complete. Stamp it with a format file. */
  SVN_ERR(svn_fs_x__write_format(dst_fs, TRUE, scratch_pool));

  return SVN_NO_ERROR;
}