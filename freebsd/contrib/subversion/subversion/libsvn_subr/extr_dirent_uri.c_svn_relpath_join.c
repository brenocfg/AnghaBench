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
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 char* apr_palloc (int /*<<< orphan*/ *,scalar_t__) ; 
 char* apr_pmemdup (int /*<<< orphan*/ *,char const*,scalar_t__) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,scalar_t__) ; 
 int /*<<< orphan*/  relpath_is_canonical (char const*) ; 
 scalar_t__ strlen (char const*) ; 

char *
svn_relpath_join(const char *base,
                 const char *component,
                 apr_pool_t *pool)
{
  apr_size_t blen = strlen(base);
  apr_size_t clen = strlen(component);
  char *path;

  assert(relpath_is_canonical(base));
  assert(relpath_is_canonical(component));

  /* If either is empty return the other */
  if (blen == 0)
    return apr_pmemdup(pool, component, clen + 1);
  if (clen == 0)
    return apr_pmemdup(pool, base, blen + 1);

  path = apr_palloc(pool, blen + 1 + clen + 1);
  memcpy(path, base, blen);
  path[blen] = '/';
  memcpy(path + blen + 1, component, clen + 1);

  return path;
}