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
 int /*<<< orphan*/  SVN_VA_NULL ; 
 char const* apr_pstrcat (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_relpath_canonicalize (char const*,int /*<<< orphan*/ *) ; 

const char *
svn_fspath__canonicalize(const char *fspath,
                         apr_pool_t *pool)
{
  if ((fspath[0] == '/') && (fspath[1] == '\0'))
    return "/";

  return apr_pstrcat(pool, "/", svn_relpath_canonicalize(fspath, pool),
                     SVN_VA_NULL);
}