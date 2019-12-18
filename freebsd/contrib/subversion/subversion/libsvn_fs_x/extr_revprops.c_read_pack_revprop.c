#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_7__ {int /*<<< orphan*/  revprops; int /*<<< orphan*/  entry; int /*<<< orphan*/  revision; } ;
typedef  TYPE_1__ packed_revprops_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_NO_SUCH_REVISION ; 
 int /*<<< orphan*/  SVN_ERR_FS_PACKED_REVPROP_READ_FAILURE ; 
 int /*<<< orphan*/  SVN_ERR_W (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SVN_FS_X__RECOVERABLE_RETRY_COUNT ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_psprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 char* get_revprop_pack_filepath (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_revprop_packname (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ has_revprop_cache (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_packed_revprops (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_revprop_generation (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__is_packed_revprop (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__try_stringbuf_from_file (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__update_min_unpacked_rev (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
read_pack_revprop(packed_revprops_t **revprops,
                  svn_fs_t *fs,
                  svn_revnum_t rev,
                  svn_boolean_t read_all,
                  apr_pool_t *result_pool,
                  apr_pool_t *scratch_pool)
{
  apr_pool_t *iterpool = svn_pool_create(scratch_pool);
  svn_boolean_t missing = FALSE;
  packed_revprops_t *result;
  int i;

  /* someone insisted that REV is packed. Double-check if necessary */
  if (!svn_fs_x__is_packed_revprop(fs, rev))
     SVN_ERR(svn_fs_x__update_min_unpacked_rev(fs, iterpool));

  if (!svn_fs_x__is_packed_revprop(fs, rev))
    return svn_error_createf(SVN_ERR_FS_NO_SUCH_REVISION, NULL,
                              _("No such packed revision %ld"), rev);

  /* initialize the result data structure */
  result = apr_pcalloc(result_pool, sizeof(*result));
  result->revision = rev;

  /* try to read the packed revprops. This may require retries if we have
   * concurrent writers. */
  for (i = 0; i < SVN_FS_X__RECOVERABLE_RETRY_COUNT; ++i)
    {
      const char *file_path;
      svn_stringbuf_t *contents = NULL;

      svn_pool_clear(iterpool);

      /* there might have been concurrent writes.
       * Re-read the manifest and the pack file.
       */
      SVN_ERR(get_revprop_packname(fs, result, result_pool, iterpool));
      file_path = get_revprop_pack_filepath(result, &result->entry,
                                            iterpool);
      SVN_ERR(svn_fs_x__try_stringbuf_from_file(&contents,
                                &missing,
                                file_path,
                                i + 1 < SVN_FS_X__RECOVERABLE_RETRY_COUNT,
                                iterpool));

      if (contents)
        {
          SVN_ERR_W(parse_packed_revprops(fs, result, contents, read_all,
                                          result_pool, iterpool),
                    apr_psprintf(iterpool,
                                 "Revprop pack file for r%ld is corrupt",
                                 rev));
          break;
        }

      /* If we could not find the file, there was a write.
       * So, we should refresh our revprop generation info as well such
       * that others may find data we will put into the cache.  They would
       * consider it outdated, otherwise.
       */
      if (missing && has_revprop_cache(fs, iterpool))
        SVN_ERR(read_revprop_generation(fs, iterpool));
    }

  /* the file content should be available now */
  if (!result->revprops)
    return svn_error_createf(SVN_ERR_FS_PACKED_REVPROP_READ_FAILURE, NULL,
                  _("Failed to read revprop pack file for r%ld"), rev);

  *revprops = result;

  return SVN_NO_ERROR;
}