#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_W (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SVN_FS_X__RECOVERABLE_RETRY_COUNT ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_psprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_revprop (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__path_revprops (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__try_stringbuf_from_file (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_string_create_from_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verify_checksum (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
read_non_packed_revprop(apr_hash_t **properties,
                        svn_fs_t *fs,
                        svn_revnum_t rev,
                        apr_pool_t *result_pool,
                        apr_pool_t *scratch_pool)
{
  svn_stringbuf_t *content = NULL;
  apr_pool_t *iterpool = svn_pool_create(scratch_pool);
  svn_boolean_t missing = FALSE;
  int i;

  for (i = 0;
       i < SVN_FS_X__RECOVERABLE_RETRY_COUNT && !missing && !content;
       ++i)
    {
      svn_pool_clear(iterpool);
      SVN_ERR(svn_fs_x__try_stringbuf_from_file(&content,
                                  &missing,
                                  svn_fs_x__path_revprops(fs, rev, iterpool),
                                  i + 1 < SVN_FS_X__RECOVERABLE_RETRY_COUNT,
                                  iterpool));
    }

  if (content)
    {
      svn_string_t *as_string;

      /* Consistency check. */
      SVN_ERR_W(verify_checksum(content, scratch_pool),
                apr_psprintf(scratch_pool,
                             "Revprop file for r%ld is corrupt",
                             rev));

      /* The contents string becomes part of the *PROPERTIES structure, i.e.
       * we must make sure it lives at least as long as the latter. */
      as_string = svn_string_create_from_buf(content, result_pool);
      SVN_ERR(parse_revprop(properties, fs, rev, as_string,
                            result_pool, iterpool));
    }

  svn_pool_clear(iterpool);

  return SVN_NO_ERROR;
}