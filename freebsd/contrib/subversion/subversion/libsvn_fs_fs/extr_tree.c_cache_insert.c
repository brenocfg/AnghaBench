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
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_5__ {int last_hit; int /*<<< orphan*/  insertions; int /*<<< orphan*/  pool; TYPE_2__* buckets; } ;
typedef  TYPE_1__ fs_fs_dag_cache_t ;
typedef  int /*<<< orphan*/  dag_node_t ;
struct TYPE_6__ {int hash_value; int path_len; int /*<<< orphan*/  node; int /*<<< orphan*/  path; int /*<<< orphan*/  revision; } ;
typedef  TYPE_2__ cache_entry_t ;
typedef  int apr_uint32_t ;
typedef  int apr_size_t ;

/* Variables and functions */
 int BUCKET_COUNT ; 
 int /*<<< orphan*/  apr_palloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  auto_clear_dag_cache (TYPE_1__*) ; 
 int hash_func (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  svn_fs_fs__dag_dup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cache_insert(fs_fs_dag_cache_t *cache,
             svn_revnum_t revision,
             const char *path,
             dag_node_t *node)
{
  apr_size_t bucket_index;
  apr_size_t path_len = strlen(path);
  apr_uint32_t hash_value;
  cache_entry_t *entry;

  auto_clear_dag_cache(cache);

  /* calculate the bucket index to use */
  hash_value = hash_func(revision, path, path_len);

  bucket_index = hash_value + (hash_value >> 16);
  bucket_index = (bucket_index + (bucket_index >> 8)) % BUCKET_COUNT;

  /* access the corresponding bucket and remember its location */
  entry = &cache->buckets[bucket_index];
  cache->last_hit = bucket_index;

  /* if it is *NOT* a match,  clear the bucket, expect the caller to fill
     in the node and count it as an insertion */
  entry->hash_value = hash_value;
  entry->revision = revision;
  if (entry->path_len < path_len)
    entry->path = apr_palloc(cache->pool, path_len + 1);
  entry->path_len = path_len;
  memcpy(entry->path, path, path_len + 1);

  entry->node = svn_fs_fs__dag_dup(node, cache->pool);
  cache->insertions++;
}