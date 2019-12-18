#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  scalar_t__ svn_wc__db_status_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  scalar_t__ svn_node_kind_t ;
struct TYPE_15__ {scalar_t__ kind; scalar_t__ filesize; scalar_t__ mtime; } ;
typedef  TYPE_1__ svn_io_dirent2_t ;
typedef  scalar_t__ svn_filesize_t ;
struct TYPE_16__ {int /*<<< orphan*/  apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  scalar_t__ apr_time_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ APR_STATUS_IS_EACCES (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_2__*) ; 
 int /*<<< orphan*/  SVN_ERR_WC_PATH_ACCESS_DENIED ; 
 scalar_t__ SVN_INVALID_FILESIZE ; 
 TYPE_2__* SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 TYPE_2__* compare_and_verify (scalar_t__*,int /*<<< orphan*/ *,char const*,scalar_t__,int /*<<< orphan*/ *,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_error_create (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_io_stat_dirent2 (TYPE_1__ const**,char const*,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_file ; 
 TYPE_2__* svn_wc__db_global_record_fileinfo (int /*<<< orphan*/ *,char const*,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_wc__db_pristine_read (int /*<<< orphan*/ **,scalar_t__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_wc__db_read_info (scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc__db_status_added ; 
 scalar_t__ svn_wc__db_status_normal ; 
 TYPE_2__* svn_wc__db_wclock_owns_lock (scalar_t__*,int /*<<< orphan*/ *,char const*,scalar_t__,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__internal_file_modified_p(svn_boolean_t *modified_p,
                                 svn_wc__db_t *db,
                                 const char *local_abspath,
                                 svn_boolean_t exact_comparison,
                                 apr_pool_t *scratch_pool)
{
  svn_stream_t *pristine_stream;
  svn_filesize_t pristine_size;
  svn_wc__db_status_t status;
  svn_node_kind_t kind;
  const svn_checksum_t *checksum;
  svn_filesize_t recorded_size;
  apr_time_t recorded_mod_time;
  svn_boolean_t has_props;
  svn_boolean_t props_mod;
  const svn_io_dirent2_t *dirent;

  /* Read the relevant info */
  SVN_ERR(svn_wc__db_read_info(&status, &kind, NULL, NULL, NULL, NULL, NULL,
                               NULL, NULL, NULL, &checksum, NULL, NULL, NULL,
                               NULL, NULL, NULL,
                               &recorded_size, &recorded_mod_time,
                               NULL, NULL, NULL, &has_props, &props_mod,
                               NULL, NULL, NULL,
                               db, local_abspath,
                               scratch_pool, scratch_pool));

  /* If we don't have a pristine or the node has a status that allows a
     pristine, just say that the node is modified */
  if (!checksum
      || (kind != svn_node_file)
      || ((status != svn_wc__db_status_normal)
          && (status != svn_wc__db_status_added)))
    {
      *modified_p = TRUE;
      return SVN_NO_ERROR;
    }

  SVN_ERR(svn_io_stat_dirent2(&dirent, local_abspath, FALSE, TRUE,
                              scratch_pool, scratch_pool));

  if (dirent->kind != svn_node_file)
    {
      /* There is no file on disk, so the text is missing, not modified. */
      *modified_p = FALSE;
      return SVN_NO_ERROR;
    }

  if (! exact_comparison)
    {
      /* We're allowed to use a heuristic to determine whether files may
         have changed.  The heuristic has these steps:

         1. Compare the working file's size
            with the size cached in the entries file
         2. If they differ, do a full file compare
         3. Compare the working file's timestamp
            with the timestamp cached in the entries file
         4. If they differ, do a full file compare
         5. Otherwise, return indicating an unchanged file.

         There are 2 problematic situations which may occur:

         1. The cached working size is missing
         --> In this case, we forget we ever tried to compare
             and skip to the timestamp comparison.  This is
             because old working copies do not contain cached sizes

         2. The cached timestamp is missing
         --> In this case, we forget we ever tried to compare
             and skip to full file comparison.  This is because
             the timestamp will be removed when the library
             updates a locally changed file.  (ie, this only happens
             when the file was locally modified.)

      */

      /* Compare the sizes, if applicable */
      if (recorded_size != SVN_INVALID_FILESIZE
          && dirent->filesize != recorded_size)
        goto compare_them;

      /* Compare the timestamps

         Note: recorded_mod_time == 0 means not available,
               which also means the timestamps won't be equal,
               so there's no need to explicitly check the 'absent' value. */
      if (recorded_mod_time != dirent->mtime)
        goto compare_them;

      *modified_p = FALSE;
      return SVN_NO_ERROR;
    }

 compare_them:
  SVN_ERR(svn_wc__db_pristine_read(&pristine_stream, &pristine_size,
                                   db, local_abspath, checksum,
                                   scratch_pool, scratch_pool));

  /* Check all bytes, and verify checksum if requested. */
  {
    svn_error_t *err;
    err = compare_and_verify(modified_p, db,
                             local_abspath, dirent->filesize,
                             pristine_stream, pristine_size,
                             has_props, props_mod,
                             exact_comparison,
                             scratch_pool);

    /* At this point we already opened the pristine file, so we know that
       the access denied applies to the working copy path */
    if (err && APR_STATUS_IS_EACCES(err->apr_err))
      return svn_error_create(SVN_ERR_WC_PATH_ACCESS_DENIED, err, NULL);
    else
      SVN_ERR(err);
  }

  if (!*modified_p)
    {
      svn_boolean_t own_lock;

      /* The timestamp is missing or "broken" so "repair" it if we can. */
      SVN_ERR(svn_wc__db_wclock_owns_lock(&own_lock, db, local_abspath, FALSE,
                                          scratch_pool));
      if (own_lock)
        SVN_ERR(svn_wc__db_global_record_fileinfo(db, local_abspath,
                                                  dirent->filesize,
                                                  dirent->mtime,
                                                  scratch_pool));
    }

  return SVN_NO_ERROR;
}