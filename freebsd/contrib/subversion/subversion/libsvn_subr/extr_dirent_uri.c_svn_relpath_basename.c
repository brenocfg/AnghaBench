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
 char const* apr_pstrmemdup (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relpath_is_canonical (char const*) ; 
 int strlen (char const*) ; 

const char *
svn_relpath_basename(const char *relpath,
                     apr_pool_t *pool)
{
  apr_size_t len = strlen(relpath);
  apr_size_t start;

  assert(relpath_is_canonical(relpath));

  start = len;
  while (start > 0 && relpath[start - 1] != '/')
    --start;

  if (pool)
    return apr_pstrmemdup(pool, relpath + start, len - start);
  else
    return relpath + start;
}