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
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cache__t ;
typedef  scalar_t__ svn_cache__error_handler_t ;
struct dump_cache_baton_t {int /*<<< orphan*/ * cache; int /*<<< orphan*/ * pool; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 struct dump_cache_baton_t* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pool_cleanup_null ; 
 int /*<<< orphan*/  apr_pool_cleanup_register (int /*<<< orphan*/ *,struct dump_cache_baton_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_cache_statistics ; 
 int /*<<< orphan*/  svn_cache__set_error_handler (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
init_callbacks(svn_cache__t *cache,
               svn_fs_t *fs,
               svn_cache__error_handler_t error_handler,
               apr_pool_t *pool)
{
  if (cache != NULL)
    {
#ifdef SVN_DEBUG_CACHE_DUMP_STATS

      /* schedule printing the access statistics upon pool cleanup,
       * i.e. end of FSFS session.
       */
      struct dump_cache_baton_t *baton;

      baton = apr_palloc(pool, sizeof(*baton));
      baton->pool = pool;
      baton->cache = cache;

      apr_pool_cleanup_register(pool,
                                baton,
                                dump_cache_statistics,
                                apr_pool_cleanup_null);
#endif

      if (error_handler)
        SVN_ERR(svn_cache__set_error_handler(cache,
                                             error_handler,
                                             fs,
                                             pool));

    }

  return SVN_NO_ERROR;
}