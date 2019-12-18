#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* set_svn_fs_open ) (TYPE_1__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* create ) (TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ fs_library_vtable_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_OS_DEFAULT ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_FS_TYPE_BDB ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  common_pool ; 
 int /*<<< orphan*/  common_pool_lock ; 
 int /*<<< orphan*/  get_library_vtable (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_open2 ; 
 int /*<<< orphan*/  svn_io_dir_make_sgid (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_fs_type (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

svn_error_t *
svn_fs_create_berkeley(svn_fs_t *fs, const char *path)
{
  fs_library_vtable_t *vtable;

  SVN_ERR(get_library_vtable(&vtable, SVN_FS_TYPE_BDB, fs->pool));

  /* Create the FS directory and write out the fsap-name file. */
  SVN_ERR(svn_io_dir_make_sgid(path, APR_OS_DEFAULT, fs->pool));
  SVN_ERR(write_fs_type(path, SVN_FS_TYPE_BDB, fs->pool));

  /* Perform the actual creation. */
  SVN_ERR(vtable->create(fs, path, common_pool_lock, fs->pool, common_pool));
  SVN_ERR(vtable->set_svn_fs_open(fs, svn_fs_open2));

  return SVN_NO_ERROR;
}