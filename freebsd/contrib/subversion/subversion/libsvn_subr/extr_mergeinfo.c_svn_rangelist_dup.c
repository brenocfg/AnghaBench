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
typedef  int /*<<< orphan*/  svn_rangelist_t ;
typedef  int /*<<< orphan*/  svn_merge_range_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * ptr_array_dup (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *) ; 

svn_rangelist_t *
svn_rangelist_dup(const svn_rangelist_t *rangelist, apr_pool_t *pool)
{
  return ptr_array_dup(rangelist, sizeof(svn_merge_range_t), pool);
}