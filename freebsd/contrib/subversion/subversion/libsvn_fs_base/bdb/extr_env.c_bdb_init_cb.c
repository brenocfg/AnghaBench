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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  apr_hash_make (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_pool_cleanup_null ; 
 int /*<<< orphan*/  apr_pool_cleanup_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bdb_cache ; 
 int /*<<< orphan*/  bdb_cache_lock ; 
 int /*<<< orphan*/  bdb_cache_pool ; 
 int /*<<< orphan*/  clear_cache ; 
 int /*<<< orphan*/  svn_mutex__init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_create (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
bdb_init_cb(void *baton, apr_pool_t *pool)
{
  bdb_cache_pool = svn_pool_create(pool);
  bdb_cache = apr_hash_make(bdb_cache_pool);

  SVN_ERR(svn_mutex__init(&bdb_cache_lock, TRUE, bdb_cache_pool));
  apr_pool_cleanup_register(bdb_cache_pool, NULL, clear_cache,
                            apr_pool_cleanup_null);

  return SVN_NO_ERROR;
}