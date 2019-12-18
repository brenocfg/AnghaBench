#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ svn_membuffer_cache_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cache__partial_getter_func_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_MUTEX__WITH_LOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_membuffer_cache_get_partial (void**,int /*<<< orphan*/ *,void*,void const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
svn_membuffer_cache_get_partial_synced(void **value_p,
                                       svn_boolean_t *found,
                                       void *cache_void,
                                       const void *key,
                                       svn_cache__partial_getter_func_t func,
                                       void *baton,
                                       apr_pool_t *result_pool)
{
  svn_membuffer_cache_t *cache = cache_void;
  SVN_MUTEX__WITH_LOCK(cache->mutex,
                       svn_membuffer_cache_get_partial(value_p,
                                                       found,
                                                       cache_void,
                                                       key,
                                                       func,
                                                       baton,
                                                       result_pool));

  return SVN_NO_ERROR;
}