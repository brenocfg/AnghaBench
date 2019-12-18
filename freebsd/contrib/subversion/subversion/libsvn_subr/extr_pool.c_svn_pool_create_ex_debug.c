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
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_allocator_t ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_pool_create_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

apr_pool_t *
svn_pool_create_ex_debug(apr_pool_t *pool, apr_allocator_t *allocator,
                         const char *file_line)
{
  return svn_pool_create_ex(pool, allocator);
}