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
struct TYPE_6__ {int /*<<< orphan*/  cache_internal; TYPE_1__* vtable; scalar_t__ pretend_empty; } ;
typedef  TYPE_2__ svn_cache__t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* has_key ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * handle_error (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_cache__has_key(svn_boolean_t *found,
                   svn_cache__t *cache,
                   const void *key,
                   apr_pool_t *scratch_pool)
{
  *found = FALSE;
#ifdef SVN_DEBUG
  if (cache->pretend_empty)
    return SVN_NO_ERROR;
#endif

  return handle_error(cache,
                      (cache->vtable->has_key)(found,
                                               cache->cache_internal,
                                               key,
                                               scratch_pool),
                      scratch_pool);
}