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
typedef  int /*<<< orphan*/  svn_lock_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_dirent_t ;
struct list_func_wrapper_baton {int /*<<< orphan*/  list_func1_baton; int /*<<< orphan*/ * (* list_func1 ) (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
list_func_wrapper(void *baton,
                  const char *path,
                  const svn_dirent_t *dirent,
                  const svn_lock_t *lock,
                  const char *abs_path,
                  const char *external_parent_url,
                  const char *external_target,
                  apr_pool_t *scratch_pool)
{
  struct list_func_wrapper_baton *lfwb = baton;

  if (lfwb->list_func1)
    return lfwb->list_func1(lfwb->list_func1_baton, path, dirent,
                           lock, abs_path, scratch_pool);

  return SVN_NO_ERROR;
}