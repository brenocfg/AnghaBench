#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  unused_pools; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ svn_root_pools__t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * apr_allocator_owner_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_array_make (int /*<<< orphan*/ *,int,int) ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_mutex__init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_create_allocator (int /*<<< orphan*/ ) ; 

svn_error_t *
svn_root_pools__create(svn_root_pools__t **pools)
{
  /* the collection of root pools must be managed independently from
     any other pool */
  apr_pool_t *pool
    = apr_allocator_owner_get(svn_pool_create_allocator(FALSE));

  /* construct result object */
  svn_root_pools__t *result = apr_pcalloc(pool, sizeof(*result));
  SVN_ERR(svn_mutex__init(&result->mutex, TRUE, pool));
  result->unused_pools = apr_array_make(pool, 16, sizeof(apr_pool_t *));

  /* done */
  *pools = result;

  return SVN_NO_ERROR;
}