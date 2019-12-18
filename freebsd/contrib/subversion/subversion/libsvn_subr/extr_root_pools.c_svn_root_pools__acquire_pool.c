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
typedef  int /*<<< orphan*/  svn_root_pools__t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * acquire_pool_internal (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_allocator_owner_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_create_allocator (int /*<<< orphan*/ ) ; 

apr_pool_t *
svn_root_pools__acquire_pool(svn_root_pools__t *pools)
{
  apr_pool_t *pool;
  svn_error_t *err = acquire_pool_internal(&pool, pools);
  if (err)
    {
      /* Mutex failure?!  Well, try to continue with unrecycled data. */
      svn_error_clear(err);
      pool = apr_allocator_owner_get(svn_pool_create_allocator(FALSE));
    }

  return pool;
}