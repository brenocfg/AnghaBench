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
typedef  int /*<<< orphan*/  svn_fs_fsfs_info_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 void* apr_pmemdup (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void *
fs_info_dup(const void *fsfs_info_void,
            apr_pool_t *result_pool)
{
  /* All fields are either ints or static strings. */
  const svn_fs_fsfs_info_t *fsfs_info = fsfs_info_void;
  return apr_pmemdup(result_pool, fsfs_info, sizeof(*fsfs_info));
}