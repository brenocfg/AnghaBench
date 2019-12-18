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
typedef  int /*<<< orphan*/  svn_fs_path_change_kind_t ;
typedef  int /*<<< orphan*/  svn_fs_path_change3_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_fs__path_change_create_internal2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_fs_path_change3_t *
svn_fs_path_change3_create(svn_fs_path_change_kind_t change_kind,
                           apr_pool_t *result_pool)
{
  return svn_fs__path_change_create_internal2(change_kind, result_pool);
}