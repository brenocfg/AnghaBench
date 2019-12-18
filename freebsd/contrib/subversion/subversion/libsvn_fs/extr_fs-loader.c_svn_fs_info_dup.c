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
struct TYPE_5__ {int /*<<< orphan*/  fs_type; } ;
typedef  TYPE_1__ svn_fs_info_placeholder_t ;
struct TYPE_6__ {void* (* info_fsap_dup ) (void const*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ fs_library_vtable_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 void* apr_pmemdup (int /*<<< orphan*/ *,TYPE_1__ const*,int) ; 
 int /*<<< orphan*/  get_library_vtable (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* stub1 (void const*,int /*<<< orphan*/ *) ; 

void *
svn_fs_info_dup(const void *info_void,
                apr_pool_t *result_pool,
                apr_pool_t *scratch_pool)
{
  const svn_fs_info_placeholder_t *info = info_void;
  fs_library_vtable_t *vtable;

  SVN_ERR(get_library_vtable(&vtable, info->fs_type, scratch_pool));

  if (vtable->info_fsap_dup)
    return vtable->info_fsap_dup(info_void, result_pool);
  else
    return apr_pmemdup(result_pool, info, sizeof(*info));
}