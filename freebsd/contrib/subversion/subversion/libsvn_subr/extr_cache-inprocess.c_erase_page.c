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
struct cache_page {int /*<<< orphan*/ * next; int /*<<< orphan*/ * prev; struct cache_entry* first_entry; int /*<<< orphan*/  page_pool; } ;
struct cache_entry {int /*<<< orphan*/  key; scalar_t__ size; struct cache_entry* next_entry; } ;
struct TYPE_3__ {scalar_t__ partial_page_number_filled; struct cache_page* partial_page; int /*<<< orphan*/  klen; int /*<<< orphan*/  hash; int /*<<< orphan*/  data_size; } ;
typedef  TYPE_1__ inprocess_cache_t ;

/* Variables and functions */
 int /*<<< orphan*/  apr_hash_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_page_from_list (struct cache_page*) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
erase_page(inprocess_cache_t *cache,
           struct cache_page *page)
{
  struct cache_entry *e;

  remove_page_from_list(page);

  for (e = page->first_entry;
       e;
       e = e->next_entry)
    {
      cache->data_size -= e->size;
      apr_hash_set(cache->hash, e->key, cache->klen, NULL);
    }

  svn_pool_clear(page->page_pool);

  page->first_entry = NULL;
  page->prev = NULL;
  page->next = NULL;

  cache->partial_page = page;
  cache->partial_page_number_filled = 0;
}