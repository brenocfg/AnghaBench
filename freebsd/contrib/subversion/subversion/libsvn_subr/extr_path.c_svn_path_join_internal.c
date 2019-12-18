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
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ SVN_PATH_IS_EMPTY (char const*) ; 
 char* apr_palloc (int /*<<< orphan*/ *,int) ; 
 char* apr_pmemdup (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  svn_path_is_canonical_internal (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *
svn_path_join_internal(const char *base,
                       const char *component,
                       apr_pool_t *pool)
{
  apr_size_t blen = strlen(base);
  apr_size_t clen = strlen(component);
  char *path;

  assert(svn_path_is_canonical_internal(base, pool));
  assert(svn_path_is_canonical_internal(component, pool));

  /* If the component is absolute, then return it.  */
  if (*component == '/')
    return apr_pmemdup(pool, component, clen + 1);

  /* If either is empty return the other */
  if (SVN_PATH_IS_EMPTY(base))
    return apr_pmemdup(pool, component, clen + 1);
  if (SVN_PATH_IS_EMPTY(component))
    return apr_pmemdup(pool, base, blen + 1);

  if (blen == 1 && base[0] == '/')
    blen = 0; /* Ignore base, just return separator + component */

  /* Construct the new, combined path. */
  path = apr_palloc(pool, blen + 1 + clen + 1);
  memcpy(path, base, blen);
  path[blen] = '/';
  memcpy(path + blen + 1, component, clen + 1);

  return path;
}