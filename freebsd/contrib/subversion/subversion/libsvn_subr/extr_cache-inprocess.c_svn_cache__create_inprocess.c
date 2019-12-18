#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_6__ {int pretend_empty; TYPE_3__* cache_internal; int /*<<< orphan*/ * vtable; } ;
typedef  TYPE_2__ svn_cache__t ;
typedef  int /*<<< orphan*/  svn_cache__serialize_func_t ;
typedef  int /*<<< orphan*/  svn_cache__deserialize_func_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_7__ {int klen; int total_pages; int unallocated_pages; int items_per_page; int /*<<< orphan*/ * cache_pool; int /*<<< orphan*/  mutex; TYPE_1__* sentinel; int /*<<< orphan*/  deserialize_func; int /*<<< orphan*/  serialize_func; int /*<<< orphan*/  hash; int /*<<< orphan*/  id; } ;
typedef  TYPE_3__ inprocess_cache_t ;
typedef  int apr_ssize_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int apr_int64_t ;
struct TYPE_5__ {struct TYPE_5__* next; struct TYPE_5__* prev; } ;

/* Variables and functions */
 int APR_HASH_KEY_STRING ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_hash_make (int /*<<< orphan*/ *) ; 
 void* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  getenv (char*) ; 
 int /*<<< orphan*/  inprocess_cache_vtable ; 
 int /*<<< orphan*/  svn_mutex__init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_cache__create_inprocess(svn_cache__t **cache_p,
                            svn_cache__serialize_func_t serialize,
                            svn_cache__deserialize_func_t deserialize,
                            apr_ssize_t klen,
                            apr_int64_t pages,
                            apr_int64_t items_per_page,
                            svn_boolean_t thread_safe,
                            const char *id,
                            apr_pool_t *pool)
{
  svn_cache__t *wrapper = apr_pcalloc(pool, sizeof(*wrapper));
  inprocess_cache_t *cache = apr_pcalloc(pool, sizeof(*cache));

  cache->id = apr_pstrdup(pool, id);

  SVN_ERR_ASSERT(klen == APR_HASH_KEY_STRING || klen >= 1);

  cache->hash = apr_hash_make(pool);
  cache->klen = klen;

  cache->serialize_func = serialize;
  cache->deserialize_func = deserialize;

  SVN_ERR_ASSERT(pages >= 1);
  cache->total_pages = pages;
  cache->unallocated_pages = pages;
  SVN_ERR_ASSERT(items_per_page >= 1);
  cache->items_per_page = items_per_page;

  cache->sentinel = apr_pcalloc(pool, sizeof(*(cache->sentinel)));
  cache->sentinel->prev = cache->sentinel;
  cache->sentinel->next = cache->sentinel;
  /* The sentinel doesn't need a pool.  (We're happy to crash if we
   * accidentally try to treat it like a real page.) */

  SVN_ERR(svn_mutex__init(&cache->mutex, thread_safe, pool));

  cache->cache_pool = pool;

  wrapper->vtable = &inprocess_cache_vtable;
  wrapper->cache_internal = cache;
  wrapper->pretend_empty = !!getenv("SVN_X_DOES_NOT_MARK_THE_SPOT");

  *cache_p = wrapper;
  return SVN_NO_ERROR;
}