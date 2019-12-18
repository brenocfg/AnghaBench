#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_mutex__t ;
struct TYPE_3__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static svn_error_t *
base_open_for_recovery(svn_fs_t *fs,
                       const char *path,
                       svn_mutex__t *common_pool_lock,
                       apr_pool_t *pool,
                       apr_pool_t *common_pool)
{
  /* Just stash the path in the fs pointer - it's all we really need. */
  fs->path = apr_pstrdup(fs->pool, path);

  return SVN_NO_ERROR;
}