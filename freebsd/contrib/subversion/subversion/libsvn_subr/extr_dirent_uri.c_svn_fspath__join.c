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
 char* apr_pstrcat (int /*<<< orphan*/ *,char const*,char const*,char const*,...) ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fspath__is_canonical (char const*) ; 
 int /*<<< orphan*/  svn_relpath_is_canonical (char const*) ; 

char *
svn_fspath__join(const char *fspath,
                 const char *relpath,
                 apr_pool_t *result_pool)
{
  char *result;
  assert(svn_fspath__is_canonical(fspath));
  assert(svn_relpath_is_canonical(relpath));

  if (relpath[0] == '\0')
    result = apr_pstrdup(result_pool, fspath);
  else if (fspath[1] == '\0')
    result = apr_pstrcat(result_pool, "/", relpath, SVN_VA_NULL);
  else
    result = apr_pstrcat(result_pool, fspath, "/", relpath, SVN_VA_NULL);

  assert(svn_fspath__is_canonical(result));
  return result;
}