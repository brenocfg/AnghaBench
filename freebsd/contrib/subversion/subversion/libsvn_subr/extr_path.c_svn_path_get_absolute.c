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
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * svn_dirent_get_absolute (char const**,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_path_is_url (char const*) ; 

svn_error_t *
svn_path_get_absolute(const char **pabsolute,
                      const char *relative,
                      apr_pool_t *pool)
{
  if (svn_path_is_url(relative))
    {
      *pabsolute = apr_pstrdup(pool, relative);
      return SVN_NO_ERROR;
    }

  return svn_dirent_get_absolute(pabsolute, relative, pool);
}