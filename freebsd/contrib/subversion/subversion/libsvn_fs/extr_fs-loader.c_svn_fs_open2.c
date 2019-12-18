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
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_svn_fs_open ) (int /*<<< orphan*/ *,int /*<<< orphan*/ * (*) (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *)) ;int /*<<< orphan*/  (* open_fs ) (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ fs_library_vtable_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  common_pool ; 
 int /*<<< orphan*/  common_pool_lock ; 
 int /*<<< orphan*/  fs_library_vtable (TYPE_1__**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fs_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ * (*) (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *)) ; 

svn_error_t *
svn_fs_open2(svn_fs_t **fs_p, const char *path, apr_hash_t *fs_config,
             apr_pool_t *result_pool,
             apr_pool_t *scratch_pool)
{
  fs_library_vtable_t *vtable;

  SVN_ERR(fs_library_vtable(&vtable, path, scratch_pool));
  *fs_p = fs_new(fs_config, result_pool);
  SVN_ERR(vtable->open_fs(*fs_p, path, common_pool_lock, scratch_pool,
                          common_pool));
  SVN_ERR(vtable->set_svn_fs_open(*fs_p, svn_fs_open2));

  return SVN_NO_ERROR;
}