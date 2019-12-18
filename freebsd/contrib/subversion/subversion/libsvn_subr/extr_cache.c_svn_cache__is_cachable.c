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
struct TYPE_5__ {int /*<<< orphan*/  cache_internal; TYPE_1__* vtable; } ;
typedef  TYPE_2__ svn_cache__t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* is_cachable ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

svn_boolean_t
svn_cache__is_cachable(svn_cache__t *cache,
                       apr_size_t size)
{
  /* having no cache means we can't cache anything */
  if (cache == NULL)
    return FALSE;

  return cache->vtable->is_cachable(cache->cache_internal, size);
}