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
typedef  int apr_off_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_BAD_VERSION_FILE_FORMAT ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  svn_ctype_isdigit (char const) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,char const,char const*) ; 

svn_error_t *
svn_fs_fs__check_file_buffer_numeric(const char *buf,
                                     apr_off_t offset,
                                     const char *path,
                                     const char *title,
                                     apr_pool_t *pool)
{
  const char *p;

  for (p = buf + offset; *p; p++)
    if (!svn_ctype_isdigit(*p))
      return svn_error_createf(SVN_ERR_BAD_VERSION_FILE_FORMAT, NULL,
        _("%s file '%s' contains unexpected non-digit '%c' within '%s'"),
        title, svn_dirent_local_style(path, pool), *p, buf);

  return SVN_NO_ERROR;
}