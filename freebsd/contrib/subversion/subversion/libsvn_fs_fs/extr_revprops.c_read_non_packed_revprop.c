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
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int SVN_FS_FS__RECOVERABLE_RETRY_COUNT ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  cache_revprops (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_revprop (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__path_revprops (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__try_stringbuf_from_file (int /*<<< orphan*/ **,scalar_t__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stringbuf__morph_into_string (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
read_non_packed_revprop(apr_hash_t **properties,
                        svn_fs_t *fs,
                        svn_revnum_t rev,
                        svn_boolean_t populate_cache,
                        apr_pool_t *pool)
{
  svn_stringbuf_t *content = NULL;
  apr_pool_t *iterpool = svn_pool_create(pool);
  svn_boolean_t missing = FALSE;
  int i;

  for (i = 0;
       i < SVN_FS_FS__RECOVERABLE_RETRY_COUNT && !missing && !content;
       ++i)
    {
      svn_pool_clear(iterpool);
      SVN_ERR(svn_fs_fs__try_stringbuf_from_file(&content,
                              &missing,
                              svn_fs_fs__path_revprops(fs, rev, iterpool),
                              i + 1 < SVN_FS_FS__RECOVERABLE_RETRY_COUNT ,
                              iterpool));
    }

  if (content)
    {
      svn_string_t *as_string = svn_stringbuf__morph_into_string(content);
      SVN_ERR(parse_revprop(properties, fs, rev, as_string, pool, iterpool));

      if (populate_cache)
        SVN_ERR(cache_revprops(NULL, fs, rev, as_string, iterpool));
    }

  svn_pool_clear(iterpool);

  return SVN_NO_ERROR;
}