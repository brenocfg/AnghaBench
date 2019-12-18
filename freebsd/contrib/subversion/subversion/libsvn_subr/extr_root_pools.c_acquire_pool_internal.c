#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  mutex; TYPE_2__* unused_pools; } ;
typedef  TYPE_1__ svn_root_pools__t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_5__ {scalar_t__ nelts; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_allocator_owner_get (int /*<<< orphan*/ ) ; 
 scalar_t__ apr_array_pop (TYPE_2__*) ; 
 int /*<<< orphan*/  svn_mutex__lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_mutex__unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_create_allocator (int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
acquire_pool_internal(apr_pool_t **pool,
                      svn_root_pools__t *pools)
{
  SVN_ERR(svn_mutex__lock(pools->mutex));
  *pool = pools->unused_pools->nelts
        ? *(apr_pool_t **)apr_array_pop(pools->unused_pools)
        : apr_allocator_owner_get(svn_pool_create_allocator(FALSE));
  SVN_ERR(svn_mutex__unlock(pools->mutex, SVN_NO_ERROR));

  return SVN_NO_ERROR;
}