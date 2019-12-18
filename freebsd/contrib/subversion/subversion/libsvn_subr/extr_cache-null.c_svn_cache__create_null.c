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
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_4__ {int /*<<< orphan*/  pretend_empty; int /*<<< orphan*/  cache_internal; int /*<<< orphan*/ * vtable; } ;
typedef  TYPE_1__ svn_cache__t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  null_cache_vtable ; 

svn_error_t *
svn_cache__create_null(svn_cache__t **cache_p,
                       const char *id,
                       apr_pool_t *result_pool)
{
  svn_cache__t *cache = apr_pcalloc(result_pool, sizeof(*cache));
  cache->vtable = &null_cache_vtable;
  cache->cache_internal = apr_pstrdup(result_pool, id);
  cache->pretend_empty = FALSE; /* There is no point in pretending --
                                   this cache _is_ empty. */

  *cache_p = cache;
  return SVN_NO_ERROR;
}