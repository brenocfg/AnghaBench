#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_revnum_t ;
struct TYPE_4__ {size_t last_hit; size_t last_non_empty; TYPE_2__* buckets; } ;
typedef  TYPE_1__ fs_fs_dag_cache_t ;
typedef  int /*<<< orphan*/  dag_node_t ;
struct TYPE_5__ {scalar_t__ revision; scalar_t__ path_len; int hash_value; int /*<<< orphan*/ * node; int /*<<< orphan*/  path; } ;
typedef  TYPE_2__ cache_entry_t ;
typedef  int apr_uint32_t ;
typedef  scalar_t__ apr_size_t ;

/* Variables and functions */
 scalar_t__ BUCKET_COUNT ; 
 int hash_func (scalar_t__,char const*,scalar_t__) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char const*,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static dag_node_t *
cache_lookup( fs_fs_dag_cache_t *cache
            , svn_revnum_t revision
            , const char *path)
{
  apr_size_t bucket_index;
  apr_size_t path_len = strlen(path);
  apr_uint32_t hash_value;

  /* optimistic lookup: hit the same bucket again? */
  cache_entry_t *result = &cache->buckets[cache->last_hit];
  if (   (result->revision == revision)
      && (result->path_len == path_len)
      && !memcmp(result->path, path, path_len))
    {
      /* Remember the position of the last node we found in this cache. */
      if (result->node)
        cache->last_non_empty = cache->last_hit;

      return result->node;
    }

  /* need to do a full lookup. */
  hash_value = hash_func(revision, path, path_len);

  bucket_index = hash_value + (hash_value >> 16);
  bucket_index = (bucket_index + (bucket_index >> 8)) % BUCKET_COUNT;

  /* access the corresponding bucket and remember its location */
  result = &cache->buckets[bucket_index];
  cache->last_hit = bucket_index;

  /* if it is *NOT* a match,  clear the bucket, expect the caller to fill
     in the node and count it as an insertion */
  if (   (result->hash_value != hash_value)
      || (result->revision != revision)
      || (result->path_len != path_len)
      || memcmp(result->path, path, path_len))
    {
      return NULL;
    }
  else if (result->node)
    {
      /* This bucket is valid & has a suitable DAG node in it.
         Remember its location. */
      cache->last_non_empty = bucket_index;
    }

  return result->node;
}