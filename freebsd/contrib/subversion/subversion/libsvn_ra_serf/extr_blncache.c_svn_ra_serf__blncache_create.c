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
struct TYPE_4__ {void* baseline_info; void* revnum_to_bc; } ;
typedef  TYPE_1__ svn_ra_serf__blncache_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 void* apr_hash_make (int /*<<< orphan*/ *) ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_ra_serf__blncache_create(svn_ra_serf__blncache_t **blncache_p,
                             apr_pool_t *pool)
{
  svn_ra_serf__blncache_t *blncache = apr_pcalloc(pool, sizeof(*blncache));
  apr_pool_t *cache_pool;

  /* Create subpool for cached data. It will be cleared if we reach maximum
   * cache size.*/
  cache_pool = svn_pool_create(pool);
  blncache->revnum_to_bc = apr_hash_make(cache_pool);
  blncache->baseline_info = apr_hash_make(cache_pool);

  *blncache_p = blncache;

  return SVN_NO_ERROR;
}