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
 char const* svn_dirent_canonicalize (char const*,int /*<<< orphan*/ *) ; 
 char* user_get_homedir (int /*<<< orphan*/ *) ; 

const char *
svn_user_get_homedir(apr_pool_t *pool)
{
  const char *homedir = user_get_homedir(pool);

  if (homedir)
    return svn_dirent_canonicalize(homedir, pool);

  return NULL;
}