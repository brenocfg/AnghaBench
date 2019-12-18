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
 int /*<<< orphan*/  adm_dir_name ; 
 char const* svn_dirent_join_many (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

const char *
svn_wc__adm_child(const char *path,
                  const char *child,
                  apr_pool_t *result_pool)
{
  return svn_dirent_join_many(result_pool,
                              path,
                              adm_dir_name,
                              child,
                              SVN_VA_NULL);
}