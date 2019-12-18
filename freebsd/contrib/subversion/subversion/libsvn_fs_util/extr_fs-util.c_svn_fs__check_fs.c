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
struct TYPE_3__ {scalar_t__ fsap_data; } ;
typedef  TYPE_1__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_FS_ALREADY_OPEN ; 
 int /*<<< orphan*/  SVN_ERR_FS_NOT_OPEN ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

svn_error_t *
svn_fs__check_fs(svn_fs_t *fs,
                 svn_boolean_t expect_open)
{
  if ((expect_open && fs->fsap_data)
      || ((! expect_open) && (! fs->fsap_data)))
    return SVN_NO_ERROR;
  if (expect_open)
    return svn_error_create(SVN_ERR_FS_NOT_OPEN, 0,
                            _("Filesystem object has not been opened yet"));
  else
    return svn_error_create(SVN_ERR_FS_ALREADY_OPEN, 0,
                            _("Filesystem object already open"));
}