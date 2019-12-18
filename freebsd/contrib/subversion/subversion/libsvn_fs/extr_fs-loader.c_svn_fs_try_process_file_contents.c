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
typedef  TYPE_2__ svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_fs_process_contents_func_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* try_process_file_contents ) (int /*<<< orphan*/ *,TYPE_2__*,char const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_2__*,char const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 

svn_error_t *
svn_fs_try_process_file_contents(svn_boolean_t *success,
                                 svn_fs_root_t *root,
                                 const char *path,
                                 svn_fs_process_contents_func_t processor,
                                 void* baton,
                                 apr_pool_t *pool)
{
  /* if the FS doesn't implement this function, report a "failed" attempt */
  if (root->vtable->try_process_file_contents == NULL)
    {
      *success = FALSE;
      return SVN_NO_ERROR;
    }

  return svn_error_trace(root->vtable->try_process_file_contents(
                         success,
                         root, path,
                         processor, baton, pool));
}