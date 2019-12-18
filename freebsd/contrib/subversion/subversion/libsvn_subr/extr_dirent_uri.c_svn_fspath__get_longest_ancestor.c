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
 char* apr_pstrcat (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fspath__is_canonical (char const*) ; 
 int /*<<< orphan*/  svn_relpath_get_longest_ancestor (char const*,char const*,int /*<<< orphan*/ *) ; 

char *
svn_fspath__get_longest_ancestor(const char *fspath1,
                                 const char *fspath2,
                                 apr_pool_t *result_pool)
{
  char *result;
  assert(svn_fspath__is_canonical(fspath1));
  assert(svn_fspath__is_canonical(fspath2));

  result = apr_pstrcat(result_pool, "/",
                       svn_relpath_get_longest_ancestor(fspath1 + 1,
                                                        fspath2 + 1,
                                                        result_pool),
                       SVN_VA_NULL);

  assert(svn_fspath__is_canonical(result));
  return result;
}