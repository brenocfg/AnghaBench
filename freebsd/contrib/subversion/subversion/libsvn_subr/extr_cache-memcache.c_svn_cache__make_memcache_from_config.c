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
struct TYPE_4__ {int /*<<< orphan*/  c; } ;
typedef  TYPE_1__ svn_memcache_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_config_t ;
struct ams_baton {int /*<<< orphan*/ * err; int /*<<< orphan*/ * memcache_pool; int /*<<< orphan*/  memcache; } ;
typedef  int /*<<< orphan*/  apr_uint16_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int APR_INT16_MAX ; 
 scalar_t__ APR_SUCCESS ; 
 int /*<<< orphan*/  SVN_CACHE_CONFIG_CATEGORY_MEMCACHED_SERVERS ; 
 int /*<<< orphan*/  SVN_ERR_NO_APR_MEMCACHE ; 
 int /*<<< orphan*/  SVN_ERR_TOO_MANY_MEMCACHED_SERVERS ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add_memcache_server ; 
 scalar_t__ apr_memcache_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nop_enumerator ; 
 int svn_config_enumerate2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ams_baton*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_wrap_apr (scalar_t__,int /*<<< orphan*/ ) ; 

svn_error_t *
svn_cache__make_memcache_from_config(svn_memcache_t **memcache_p,
                                    svn_config_t *config,
                                    apr_pool_t *result_pool,
                                    apr_pool_t *scratch_pool)
{
  int server_count =
    svn_config_enumerate2(config,
                          SVN_CACHE_CONFIG_CATEGORY_MEMCACHED_SERVERS,
                          nop_enumerator, NULL, scratch_pool);

  if (server_count == 0)
    {
      *memcache_p = NULL;
      return SVN_NO_ERROR;
    }

  if (server_count > APR_INT16_MAX)
    return svn_error_create(SVN_ERR_TOO_MANY_MEMCACHED_SERVERS, NULL, NULL);

#ifdef SVN_HAVE_MEMCACHE
  {
    struct ams_baton b;
    svn_memcache_t *memcache = apr_pcalloc(result_pool, sizeof(*memcache));
    apr_status_t apr_err = apr_memcache_create(result_pool,
                                               (apr_uint16_t)server_count,
                                               0, /* flags */
                                               &(memcache->c));
    if (apr_err != APR_SUCCESS)
      return svn_error_wrap_apr(apr_err,
                                _("Unknown error creating apr_memcache_t"));

    b.memcache = memcache->c;
    b.memcache_pool = result_pool;
    b.err = SVN_NO_ERROR;
    svn_config_enumerate2(config,
                          SVN_CACHE_CONFIG_CATEGORY_MEMCACHED_SERVERS,
                          add_memcache_server, &b,
                          scratch_pool);

    if (b.err)
      return b.err;

    *memcache_p = memcache;

    return SVN_NO_ERROR;
  }
#else /* ! SVN_HAVE_MEMCACHE */
  {
    return svn_error_create(SVN_ERR_NO_APR_MEMCACHE, NULL, NULL);
  }
#endif /* SVN_HAVE_MEMCACHE */
}