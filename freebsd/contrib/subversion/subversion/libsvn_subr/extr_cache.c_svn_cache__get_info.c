#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_9__ {scalar_t__ failures; scalar_t__ writes; scalar_t__ hits; scalar_t__ reads; int /*<<< orphan*/  cache_internal; TYPE_1__* vtable; } ;
typedef  TYPE_2__ svn_cache__t ;
struct TYPE_10__ {scalar_t__ failures; scalar_t__ sets; scalar_t__ hits; scalar_t__ gets; } ;
typedef  TYPE_3__ svn_cache__info_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* get_info ) (int /*<<< orphan*/ ,TYPE_3__*,scalar_t__,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_3__*,scalar_t__,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_cache__get_info(svn_cache__t *cache,
                    svn_cache__info_t *info,
                    svn_boolean_t reset,
                    apr_pool_t *result_pool)
{
  /* write general statistics */

  memset(info, 0, sizeof(*info));
  info->gets = cache->reads;
  info->hits = cache->hits;
  info->sets = cache->writes;
  info->failures = cache->failures;

  /* Call the cache implementation for filling the blanks.
   * It might also replace some of the general stats but
   * this is currently not done.
   */
  SVN_ERR((cache->vtable->get_info)(cache->cache_internal,
                                    info,
                                    reset,
                                    result_pool));

  /* reset statistics */

  if (reset)
    {
      cache->reads = 0;
      cache->hits = 0;
      cache->writes = 0;
      cache->failures = 0;
    }

  return SVN_NO_ERROR;
}