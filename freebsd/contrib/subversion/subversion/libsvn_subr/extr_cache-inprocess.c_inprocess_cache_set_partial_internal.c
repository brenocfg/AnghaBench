#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  (* svn_cache__partial_setter_func_t ) (int /*<<< orphan*/ *,scalar_t__*,void*,int /*<<< orphan*/ ) ;
struct cache_entry {scalar_t__ size; TYPE_3__* page; int /*<<< orphan*/  value; } ;
struct TYPE_5__ {int /*<<< orphan*/  data_size; int /*<<< orphan*/  klen; int /*<<< orphan*/  hash; } ;
typedef  TYPE_1__ inprocess_cache_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_6__ {int /*<<< orphan*/  page_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 struct cache_entry* apr_hash_get (int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  move_page_to_front (TYPE_1__*,TYPE_3__*) ; 

__attribute__((used)) static svn_error_t *
inprocess_cache_set_partial_internal(inprocess_cache_t *cache,
                                     const void *key,
                                     svn_cache__partial_setter_func_t func,
                                     void *baton,
                                     apr_pool_t *scratch_pool)
{
  struct cache_entry *entry = apr_hash_get(cache->hash, key, cache->klen);
  if (entry)
    {
      SVN_ERR(move_page_to_front(cache, entry->page));

      cache->data_size -= entry->size;
      SVN_ERR(func(&entry->value,
                   &entry->size,
                   baton,
                   entry->page->page_pool));
      cache->data_size += entry->size;
    }

  return SVN_NO_ERROR;
}