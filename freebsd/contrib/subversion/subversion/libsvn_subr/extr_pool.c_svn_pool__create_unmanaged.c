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
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  abort_on_pool_failure ; 
 int /*<<< orphan*/  apr_pool_create_unmanaged_ex (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_create_allocator (int /*<<< orphan*/ ) ; 

apr_pool_t *
svn_pool__create_unmanaged(svn_boolean_t thread_safe)
{
  apr_pool_t *pool;
  apr_pool_create_unmanaged_ex(&pool, abort_on_pool_failure,
                               svn_pool_create_allocator(thread_safe));
  return pool;
}