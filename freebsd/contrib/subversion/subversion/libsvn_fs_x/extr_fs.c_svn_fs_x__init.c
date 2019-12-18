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
struct TYPE_5__ {scalar_t__ major; } ;
typedef  TYPE_1__ svn_version_t ;
struct TYPE_6__ {char* member_0; int /*<<< orphan*/ * member_1; } ;
typedef  TYPE_2__ svn_version_checklist_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  fs_library_vtable_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_VERSION_MISMATCH ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ SVN_VER_MAJOR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  library_vtable ; 
#define  svn_delta_version 130 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
#define  svn_fs_util__version 129 
 int /*<<< orphan*/  svn_fs_x__batch_fsync_init (int /*<<< orphan*/ *) ; 
#define  svn_subr_version 128 
 int /*<<< orphan*/  svn_ver_check_list2 (int /*<<< orphan*/ ,TYPE_2__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_ver_equal ; 
 int /*<<< orphan*/  x_version () ; 

svn_error_t *
svn_fs_x__init(const svn_version_t *loader_version,
               fs_library_vtable_t **vtable,
               apr_pool_t* common_pool)
{
  static const svn_version_checklist_t checklist[] =
    {
      { "svn_subr",  svn_subr_version },
      { "svn_delta", svn_delta_version },
      { "svn_fs_util", svn_fs_util__version },
      { NULL, NULL }
    };

  /* Simplified version check to make sure we can safely use the
     VTABLE parameter. The FS loader does a more exhaustive check. */
  if (loader_version->major != SVN_VER_MAJOR)
    return svn_error_createf(SVN_ERR_VERSION_MISMATCH, NULL,
                             _("Unsupported FS loader version (%d) for fsx"),
                             loader_version->major);
  SVN_ERR(svn_ver_check_list2(x_version(), checklist, svn_ver_equal));

  SVN_ERR(svn_fs_x__batch_fsync_init(common_pool));

  *vtable = &library_vtable;
  return SVN_NO_ERROR;
}