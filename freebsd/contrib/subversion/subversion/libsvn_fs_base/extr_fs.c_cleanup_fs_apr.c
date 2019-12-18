#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  warning_baton; int /*<<< orphan*/  (* warning ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 
 int /*<<< orphan*/  SVN_ERR_FS_CLEANUP ; 
 int /*<<< orphan*/ * cleanup_fs (TYPE_1__*) ; 
 int /*<<< orphan*/  print_fs_stats (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 

__attribute__((used)) static apr_status_t
cleanup_fs_apr(void *data)
{
  svn_fs_t *fs = data;
  svn_error_t *err;

  print_fs_stats(fs);

  err = cleanup_fs(fs);
  if (! err)
    return APR_SUCCESS;

  /* Darn. An error during cleanup. Call the warning handler to
     try and do something "right" with this error. Note that
     the default will simply abort().  */
  (*fs->warning)(fs->warning_baton, err);

  svn_error_clear(err);

  return SVN_ERR_FS_CLEANUP;
}