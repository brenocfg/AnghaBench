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
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 
 int /*<<< orphan*/  svn_fspath__is_canonical (char const*) ; 
 char* svn_relpath_basename (char const*,int /*<<< orphan*/ *) ; 

const char *
svn_fspath__basename(const char *fspath,
                     apr_pool_t *pool)
{
  const char *result;
  assert(svn_fspath__is_canonical(fspath));

  result = svn_relpath_basename(fspath + 1, pool);

  assert(strchr(result, '/') == NULL);
  return result;
}