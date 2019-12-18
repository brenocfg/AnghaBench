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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 char* svn_dirent_canonicalize (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_utf_cstring_to_utf8 (char const**,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
grab_filename(const char **file_name, const char *line, apr_pool_t *result_pool,
              apr_pool_t *scratch_pool)
{
  const char *utf8_path;
  const char *canon_path;

  /* Grab the filename and encode it in UTF-8. */
  /* TODO: Allow specifying the patch file's encoding.
   *       For now, we assume its encoding is native. */
  /* ### This can fail if the filename cannot be represented in the current
   * ### locale's encoding. */
  SVN_ERR(svn_utf_cstring_to_utf8(&utf8_path,
                                  line,
                                  scratch_pool));

  /* Canonicalize the path name. */
  canon_path = svn_dirent_canonicalize(utf8_path, scratch_pool);

  *file_name = apr_pstrdup(result_pool, canon_path);

  return SVN_NO_ERROR;
}