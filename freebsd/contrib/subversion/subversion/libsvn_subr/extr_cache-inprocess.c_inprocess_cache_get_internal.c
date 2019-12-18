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
typedef  int /*<<< orphan*/  svn_error_t ;
struct cache_entry {scalar_t__ size; int /*<<< orphan*/  value; int /*<<< orphan*/  page; } ;
struct TYPE_4__ {int /*<<< orphan*/  klen; int /*<<< orphan*/  hash; } ;
typedef  TYPE_1__ inprocess_cache_t ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 struct cache_entry* apr_hash_get (int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ) ; 
 char* apr_palloc (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  move_page_to_front (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
inprocess_cache_get_internal(char **buffer,
                             apr_size_t *size,
                             inprocess_cache_t *cache,
                             const void *key,
                             apr_pool_t *result_pool)
{
  struct cache_entry *entry = apr_hash_get(cache->hash, key, cache->klen);

  if (entry)
    {
      SVN_ERR(move_page_to_front(cache, entry->page));

      /* duplicate the buffer entry */
      *buffer = apr_palloc(result_pool, entry->size);
      if (entry->size)
        memcpy(*buffer, entry->value, entry->size);

      *size = entry->size;
    }
  else
    {
      *buffer = NULL;
      *size = 0;
    }

  return SVN_NO_ERROR;
}