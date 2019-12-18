#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_6__ {int /*<<< orphan*/  packed_revprops; int /*<<< orphan*/  filename; int /*<<< orphan*/  folder; int /*<<< orphan*/  revision; } ;
typedef  TYPE_1__ packed_revprops_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_CORRUPT ; 
 int /*<<< orphan*/  SVN_ERR_FS_NO_SUCH_REVISION ; 
 int /*<<< orphan*/  SVN_ERR_FS_PACKED_REVPROP_READ_FAILURE ; 
 int SVN_FS_FS__RECOVERABLE_RETRY_COUNT ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_revprop_packname (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * parse_packed_revprops (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_dirent_join (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_fs__is_packed_revprop (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_fs__try_stringbuf_from_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__update_min_unpacked_rev (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
read_pack_revprop(packed_revprops_t **revprops,
                  svn_fs_t *fs,
                  svn_revnum_t rev,
                  svn_boolean_t read_all,
                  svn_boolean_t populate_cache,
                  apr_pool_t *pool)
{
  apr_pool_t *iterpool = svn_pool_create(pool);
  svn_boolean_t missing = FALSE;
  svn_error_t *err;
  packed_revprops_t *result;
  int i;

  /* someone insisted that REV is packed. Double-check if necessary */
  if (!svn_fs_fs__is_packed_revprop(fs, rev))
     SVN_ERR(svn_fs_fs__update_min_unpacked_rev(fs, iterpool));

  if (!svn_fs_fs__is_packed_revprop(fs, rev))
    return svn_error_createf(SVN_ERR_FS_NO_SUCH_REVISION, NULL,
                              _("No such packed revision %ld"), rev);

  /* initialize the result data structure */
  result = apr_pcalloc(pool, sizeof(*result));
  result->revision = rev;

  /* try to read the packed revprops. This may require retries if we have
   * concurrent writers. */
  for (i = 0;
       i < SVN_FS_FS__RECOVERABLE_RETRY_COUNT && !result->packed_revprops;
       ++i)
    {
      const char *file_path;
      svn_pool_clear(iterpool);

      /* there might have been concurrent writes.
       * Re-read the manifest and the pack file.
       */
      SVN_ERR(get_revprop_packname(fs, result, pool, iterpool));
      file_path  = svn_dirent_join(result->folder,
                                   result->filename,
                                   iterpool);
      SVN_ERR(svn_fs_fs__try_stringbuf_from_file(&result->packed_revprops,
                                &missing,
                                file_path,
                                i + 1 < SVN_FS_FS__RECOVERABLE_RETRY_COUNT,
                                pool));
    }

  /* the file content should be available now */
  if (!result->packed_revprops)
    return svn_error_createf(SVN_ERR_FS_PACKED_REVPROP_READ_FAILURE, NULL,
                  _("Failed to read revprop pack file for r%ld"), rev);

  /* parse it. RESULT will be complete afterwards. */
  err = parse_packed_revprops(fs, result, read_all, populate_cache, pool,
                              iterpool);
  svn_pool_destroy(iterpool);
  if (err)
    return svn_error_createf(SVN_ERR_FS_CORRUPT, err,
                  _("Revprop pack file for r%ld is corrupt"), rev);

  *revprops = result;

  return SVN_NO_ERROR;
}