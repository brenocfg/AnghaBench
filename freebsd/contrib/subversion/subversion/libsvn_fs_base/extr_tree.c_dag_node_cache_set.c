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
struct TYPE_4__ {int /*<<< orphan*/  pool; scalar_t__ is_txn_root; TYPE_2__* fsap_data; } ;
typedef  TYPE_1__ svn_fs_root_t ;
struct dag_node_cache_t {int idx; int /*<<< orphan*/ * pool; void* node; } ;
typedef  int /*<<< orphan*/  dag_node_t ;
struct TYPE_5__ {int node_cache_idx; char** node_cache_keys; int /*<<< orphan*/  node_cache; } ;
typedef  TYPE_2__ base_root_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int NODE_CACHE_MAX_KEYS ; 
 int /*<<< orphan*/  SVN_ERR_MALFUNCTION_NO_RETURN () ; 
 int apr_hash_count (int /*<<< orphan*/ ) ; 
 struct dag_node_cache_t* apr_palloc (int /*<<< orphan*/ *,int) ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memmove (char**,char**,int) ; 
 void* svn_fs_base__dag_dup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct dag_node_cache_t* svn_hash_gets (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ ,char const*,struct dag_node_cache_t*) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dag_node_cache_set(svn_fs_root_t *root,
                   const char *path,
                   dag_node_t *node)
{
  base_root_data_t *brd = root->fsap_data;
  const char *cache_path;
  apr_pool_t *cache_pool;
  struct dag_node_cache_t *cache_item;
  int num_keys = apr_hash_count(brd->node_cache);

  /* What?  No POOL passed to this function?

     To ensure that our cache values live as long as the svn_fs_root_t
     in which they are ultimately stored, and to allow us to free()
     them individually without harming the rest, they are each
     allocated from a subpool of ROOT's pool.  We'll keep one subpool
     around for each cache slot -- as we start expiring stuff
     to make room for more entries, we'll re-use the expired thing's
     pool. */

  /* Assert valid input and state. */
  assert(*path == '/');
  assert((brd->node_cache_idx <= num_keys)
         && (num_keys <= NODE_CACHE_MAX_KEYS));

  /* Only allow revision roots. */
  if (root->is_txn_root)
    return;

  /* Special case: the caller wants us to replace an existing cached
     node with a new one.  If the callers aren't mindless, this should
     only happen when a node is made mutable under a transaction
     root, and that only happens once under that root.  So, we'll be a
     little bit sloppy here, and count on callers doing the right
     thing. */
  cache_item = svn_hash_gets(brd->node_cache, path);
  if (cache_item)
    {
      /* ### This section is somehow broken.  I don't know how, but it
         ### is.  And I don't want to spend any more time on it.  So,
         ### callers, use only revision root and don't try to update
         ### an already-cached thing.  -- cmpilato */
      SVN_ERR_MALFUNCTION_NO_RETURN();

#if 0
      int cache_index = cache_item->idx;
      cache_path = brd->node_cache_keys[cache_index];
      cache_pool = cache_item->pool;
      cache_item->node = svn_fs_base__dag_dup(node, cache_pool);

      /* Now, move the cache key reference to the end of the keys in
         the keys array (unless it's already at the end).  ### Yes,
         it's a memmove(), but we're not talking about pages of memory
         here. */
      if (cache_index != (num_keys - 1))
        {
          int move_num = NODE_CACHE_MAX_KEYS - cache_index - 1;
          memmove(brd->node_cache_keys + cache_index,
                  brd->node_cache_keys + cache_index + 1,
                  move_num * sizeof(const char *));
          cache_index = num_keys - 1;
          brd->node_cache_keys[cache_index] = cache_path;
        }

      /* Advance the cache pointers. */
      cache_item->idx = cache_index;
      brd->node_cache_idx = (cache_index + 1) % NODE_CACHE_MAX_KEYS;
      return;
#endif
    }

  /* We're adding a new cache item.  First, see if we have room for it
     (otherwise, make some room). */
  if (apr_hash_count(brd->node_cache) == NODE_CACHE_MAX_KEYS)
    {
      /* No room.  Expire the oldest thing. */
      cache_path = brd->node_cache_keys[brd->node_cache_idx];
      cache_item = svn_hash_gets(brd->node_cache, cache_path);
      svn_hash_sets(brd->node_cache, cache_path, NULL);
      cache_pool = cache_item->pool;
      svn_pool_clear(cache_pool);
    }
  else
    {
      cache_pool = svn_pool_create(root->pool);
    }

  /* Make the cache item, allocated in its own pool. */
  cache_item = apr_palloc(cache_pool, sizeof(*cache_item));
  cache_item->node = svn_fs_base__dag_dup(node, cache_pool);
  cache_item->idx = brd->node_cache_idx;
  cache_item->pool = cache_pool;

  /* Now add it to the cache. */
  cache_path = apr_pstrdup(cache_pool, path);
  svn_hash_sets(brd->node_cache, cache_path, cache_item);
  brd->node_cache_keys[brd->node_cache_idx] = cache_path;

  /* Advance the cache pointer. */
  brd->node_cache_idx = (brd->node_cache_idx + 1) % NODE_CACHE_MAX_KEYS;
}