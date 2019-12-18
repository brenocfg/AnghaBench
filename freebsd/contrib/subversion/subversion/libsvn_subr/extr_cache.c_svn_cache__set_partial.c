#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_6__ {int /*<<< orphan*/  cache_internal; TYPE_1__* vtable; int /*<<< orphan*/  writes; } ;
typedef  TYPE_2__ svn_cache__t ;
typedef  int /*<<< orphan*/  svn_cache__partial_setter_func_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* set_partial ) (int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/ * handle_error (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_cache__set_partial(svn_cache__t *cache,
                       const void *key,
                       svn_cache__partial_setter_func_t func,
                       void *baton,
                       apr_pool_t *scratch_pool)
{
  cache->writes++;
  return handle_error(cache,
                      (cache->vtable->set_partial)(cache->cache_internal,
                                                   key,
                                                   func,
                                                   baton,
                                                   scratch_pool),
                      scratch_pool);
}