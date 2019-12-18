#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* vtable; } ;
typedef  TYPE_2__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_get_locks_callback_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_depth_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* get_locks ) (TYPE_2__*,char const*,scalar_t__,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,char const*,scalar_t__,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_depth_empty ; 
 scalar_t__ svn_depth_files ; 
 scalar_t__ svn_depth_immediates ; 
 scalar_t__ svn_depth_infinity ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 

svn_error_t *
svn_fs_get_locks2(svn_fs_t *fs, const char *path, svn_depth_t depth,
                  svn_fs_get_locks_callback_t get_locks_func,
                  void *get_locks_baton, apr_pool_t *pool)
{
  SVN_ERR_ASSERT((depth == svn_depth_empty) ||
                 (depth == svn_depth_files) ||
                 (depth == svn_depth_immediates) ||
                 (depth == svn_depth_infinity));
  return svn_error_trace(fs->vtable->get_locks(fs, path, depth,
                                               get_locks_func,
                                               get_locks_baton, pool));
}