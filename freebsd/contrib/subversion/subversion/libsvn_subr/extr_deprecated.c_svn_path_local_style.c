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
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 char const* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 char const* svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_path_is_url (char const*) ; 

const char *
svn_path_local_style(const char *path, apr_pool_t *pool)
{
  if (svn_path_is_url(path))
    return apr_pstrdup(pool, path);
  else
    return svn_dirent_local_style(path, pool);
}