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
typedef  int /*<<< orphan*/  svn_io_dirent2_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * apr_pmemdup (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

svn_io_dirent2_t *
svn_io_dirent2_dup(const svn_io_dirent2_t *item,
                   apr_pool_t *result_pool)
{
  return apr_pmemdup(result_pool,
                     item,
                     sizeof(*item));
}