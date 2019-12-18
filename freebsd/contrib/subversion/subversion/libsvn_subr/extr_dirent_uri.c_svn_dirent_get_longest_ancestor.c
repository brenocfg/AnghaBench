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
 int /*<<< orphan*/  get_longest_ancestor_length (int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  type_dirent ; 

char *
svn_dirent_get_longest_ancestor(const char *dirent1,
                                const char *dirent2,
                                apr_pool_t *pool)
{
  return apr_pstrndup(pool, dirent1,
                      get_longest_ancestor_length(type_dirent, dirent1,
                                                  dirent2, pool));
}