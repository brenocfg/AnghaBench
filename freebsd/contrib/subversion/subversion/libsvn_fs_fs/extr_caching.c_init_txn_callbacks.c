#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * pool; } ;
typedef  TYPE_1__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_cache__t ;
struct txn_cleanup_baton_t {int /*<<< orphan*/ * fs_pool; int /*<<< orphan*/ * txn_pool; int /*<<< orphan*/ ** to_reset; int /*<<< orphan*/ * txn_cache; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 struct txn_cleanup_baton_t* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pool_cleanup_null ; 
 int /*<<< orphan*/  apr_pool_cleanup_register (int /*<<< orphan*/ *,struct txn_cleanup_baton_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_txn_cache_fs ; 
 int /*<<< orphan*/  remove_txn_cache_txn ; 

__attribute__((used)) static void
init_txn_callbacks(svn_fs_t *fs,
                   svn_cache__t **cache,
                   apr_pool_t *pool)
{
  if (*cache != NULL)
    {
      struct txn_cleanup_baton_t *baton;

      baton = apr_palloc(pool, sizeof(*baton));
      baton->txn_cache = *cache;
      baton->to_reset = cache;
      baton->txn_pool = pool;
      baton->fs_pool = fs->pool;

      /* If any of these pools gets cleaned, we must reset the cache.
       * We don't know which one will get cleaned up first, so register
       * cleanup actions for both and during the cleanup action, unregister
       * the respective other action. */
      apr_pool_cleanup_register(pool,
                                baton,
                                remove_txn_cache_txn,
                                apr_pool_cleanup_null);
      apr_pool_cleanup_register(fs->pool,
                                baton,
                                remove_txn_cache_fs,
                                apr_pool_cleanup_null);
    }
}