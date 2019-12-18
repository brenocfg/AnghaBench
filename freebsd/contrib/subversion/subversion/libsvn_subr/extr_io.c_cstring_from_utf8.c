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
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * svn_path_cstring_from_utf8 (char const**,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
cstring_from_utf8(const char **path_apr,
                  const char *path_utf8,
                  apr_pool_t *pool)
{
#if defined(WIN32) || defined(DARWIN)
  *path_apr = path_utf8;
  return SVN_NO_ERROR;
#else
  return svn_path_cstring_from_utf8(path_apr, path_utf8, pool);
#endif
}