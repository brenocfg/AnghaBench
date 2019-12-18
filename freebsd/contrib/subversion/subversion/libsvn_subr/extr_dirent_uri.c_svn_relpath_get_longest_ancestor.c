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
 char* apr_pstrndup (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_longest_ancestor_length (int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  relpath_is_canonical (char const*) ; 
 int /*<<< orphan*/  type_relpath ; 

char *
svn_relpath_get_longest_ancestor(const char *relpath1,
                                 const char *relpath2,
                                 apr_pool_t *pool)
{
  assert(relpath_is_canonical(relpath1));
  assert(relpath_is_canonical(relpath2));

  return apr_pstrndup(pool, relpath1,
                      get_longest_ancestor_length(type_relpath, relpath1,
                                                  relpath2, pool));
}