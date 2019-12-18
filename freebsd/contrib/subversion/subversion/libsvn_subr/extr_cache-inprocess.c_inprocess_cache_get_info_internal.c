#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_5__ {int used_entries; int total_entries; scalar_t__ total_size; scalar_t__ data_size; scalar_t__ used_size; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ svn_cache__info_t ;
struct cache_page {int dummy; } ;
struct cache_entry {int dummy; } ;
struct TYPE_6__ {int items_per_page; int total_pages; scalar_t__ data_size; int /*<<< orphan*/  hash; int /*<<< orphan*/  id; } ;
typedef  TYPE_2__ inprocess_cache_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int apr_hash_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
inprocess_cache_get_info_internal(inprocess_cache_t *cache,
                                  svn_cache__info_t *info,
                                  apr_pool_t *result_pool)
{
  info->id = apr_pstrdup(result_pool, cache->id);

  info->used_entries = apr_hash_count(cache->hash);
  info->total_entries = cache->items_per_page * cache->total_pages;

  info->used_size = cache->data_size;
  info->data_size = cache->data_size;
  info->total_size = cache->data_size
                   + cache->items_per_page * sizeof(struct cache_page)
                   + info->used_entries * sizeof(struct cache_entry);

  return SVN_NO_ERROR;
}