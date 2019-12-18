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

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * io_set_file_perms (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_io_set_file_executable(const char *path,
                           svn_boolean_t executable,
                           svn_boolean_t ignore_enoent,
                           apr_pool_t *pool)
{
  /* On Windows and OS/2, just exit -- on unix call our internal function
  which attempts to honor the umask. */
#if (!defined(WIN32) && !defined(__OS2__))
  return io_set_file_perms(path, FALSE, FALSE, TRUE, executable,
                           ignore_enoent, pool);
#else
  return SVN_NO_ERROR;
#endif
}