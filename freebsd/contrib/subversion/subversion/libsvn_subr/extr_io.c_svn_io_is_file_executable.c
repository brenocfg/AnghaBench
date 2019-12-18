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
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_finfo_t ;

/* Variables and functions */
 int APR_FINFO_OWNER ; 
 int APR_FINFO_PROT ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_io__is_finfo_executable (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_stat (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_io_is_file_executable(svn_boolean_t *executable,
                          const char *path,
                          apr_pool_t *pool)
{
#if defined(APR_HAS_USER) && !defined(WIN32) &&!defined(__OS2__)
  apr_finfo_t file_info;

  SVN_ERR(svn_io_stat(&file_info, path, APR_FINFO_PROT | APR_FINFO_OWNER,
                      pool));
  SVN_ERR(svn_io__is_finfo_executable(executable, &file_info, pool));

#else  /* WIN32 || __OS2__ || !APR_HAS_USER */
  *executable = FALSE;
#endif

  return SVN_NO_ERROR;
}