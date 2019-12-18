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
typedef  int /*<<< orphan*/  svn_iter_apr_hash_cb_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_5__ {int /*<<< orphan*/  cache_internal; TYPE_1__* vtable; scalar_t__ pretend_empty; } ;
typedef  TYPE_2__ svn_cache__t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_4__ {int /*<<< orphan*/ * (* iter ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_cache__iter(svn_boolean_t *completed,
                svn_cache__t *cache,
                svn_iter_apr_hash_cb_t user_cb,
                void *user_baton,
                apr_pool_t *scratch_pool)
{
#ifdef SVN_DEBUG
  if (cache->pretend_empty)
    /* Pretend CACHE is empty. */
    return SVN_NO_ERROR;
#endif

  return (cache->vtable->iter)(completed,
                               cache->cache_internal,
                               user_cb,
                               user_baton,
                               scratch_pool);
}