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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_CORRUPT ; 
 int SVN_FS_X__RECOVERABLE_RETRY_COUNT ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__try_stringbuf_from_file (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_x__read_content(svn_stringbuf_t **content,
                       const char *fname,
                       apr_pool_t *result_pool)
{
  int i;
  *content = NULL;

  for (i = 0; !*content && (i < SVN_FS_X__RECOVERABLE_RETRY_COUNT); ++i)
    SVN_ERR(svn_fs_x__try_stringbuf_from_file(content, NULL,
                           fname, i + 1 < SVN_FS_X__RECOVERABLE_RETRY_COUNT,
                           result_pool));

  if (!*content)
    return svn_error_createf(SVN_ERR_FS_CORRUPT, NULL,
                             _("Can't read '%s'"),
                             svn_dirent_local_style(fname, result_pool));

  return SVN_NO_ERROR;
}