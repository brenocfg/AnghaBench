#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_iter_apr_hash_cb_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct cache_iter_baton {void* user_baton; int /*<<< orphan*/  user_cb; } ;
struct TYPE_2__ {int /*<<< orphan*/  hash; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ inprocess_cache_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_MUTEX__WITH_LOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  iter_cb ; 
 int /*<<< orphan*/  svn_iter_apr_hash (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cache_iter_baton*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
inprocess_cache_iter(svn_boolean_t *completed,
                     void *cache_void,
                     svn_iter_apr_hash_cb_t user_cb,
                     void *user_baton,
                     apr_pool_t *scratch_pool)
{
  inprocess_cache_t *cache = cache_void;
  struct cache_iter_baton b;
  b.user_cb = user_cb;
  b.user_baton = user_baton;

  SVN_MUTEX__WITH_LOCK(cache->mutex,
                       svn_iter_apr_hash(completed, cache->hash,
                                         iter_cb, &b, scratch_pool));

  return SVN_NO_ERROR;
}