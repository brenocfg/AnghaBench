#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_memcache_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cache__t ;
typedef  int /*<<< orphan*/  svn_cache__serialize_func_t ;
typedef  int /*<<< orphan*/  svn_cache__deserialize_func_t ;
typedef  int /*<<< orphan*/  apr_ssize_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_NO_APR_MEMCACHE ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_cache__create_memcache(svn_cache__t **cache_p,
                          svn_memcache_t *memcache,
                          svn_cache__serialize_func_t serialize_func,
                          svn_cache__deserialize_func_t deserialize_func,
                          apr_ssize_t klen,
                          const char *prefix,
                          apr_pool_t *pool)
{
  return svn_error_create(SVN_ERR_NO_APR_MEMCACHE, NULL, NULL);
}