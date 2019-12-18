#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_membuffer_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int apr_uint64_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_allocator_t ;
struct TYPE_4__ {scalar_t__ cache_size; } ;
struct TYPE_3__ {int /*<<< orphan*/  single_threaded; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int MIN (scalar_t__,int) ; 
 scalar_t__ SVN_MAX_OBJECT_SIZE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ apr_allocator_create (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  apr_allocator_max_free_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_allocator_owner_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_pool_create_ex (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__ cache_settings ; 
 int /*<<< orphan*/ * svn_cache__membuffer_cache_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_cache_config_get () ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
initialize_cache(void *baton, apr_pool_t *unused_pool)
{
  svn_membuffer_t **cache_p = baton;
  svn_membuffer_t *cache = NULL;

  /* Limit the cache size to about half the available address space
   * (typ. 1G under 32 bits).
   */
  apr_uint64_t cache_size = MIN(cache_settings.cache_size,
                                (apr_uint64_t)SVN_MAX_OBJECT_SIZE / 2);

  /* Create caches at all? */
  if (cache_size)
    {
      svn_error_t *err;

      /* auto-allocate cache */
      apr_allocator_t *allocator = NULL;
      apr_pool_t *pool = NULL;

      if (apr_allocator_create(&allocator))
        return SVN_NO_ERROR;

      /* Ensure that we free partially allocated data if we run OOM
       * before the cache is complete: If the cache cannot be allocated
       * in its full size, the create() function will clear the pool
       * explicitly. The allocator will make sure that any memory no
       * longer used by the pool will actually be returned to the OS.
       *
       * Please note that this pool and allocator is used *only* to
       * allocate the large membuffer. All later dynamic allocations
       * come from other, temporary pools and allocators.
       */
      apr_allocator_max_free_set(allocator, 1);

      /* don't terminate upon OOM but make pool return a NULL pointer
       * instead so we can disable caching gracefully and continue
       * operation without membuffer caches.
       */
      apr_pool_create_ex(&pool, NULL, NULL, allocator);
      if (pool == NULL)
        return SVN_NO_ERROR;
      apr_allocator_owner_set(allocator, pool);

      err = svn_cache__membuffer_cache_create(
          &cache,
          (apr_size_t)cache_size,
          (apr_size_t)(cache_size / 5),
          0,
          ! svn_cache_config_get()->single_threaded,
          FALSE,
          pool);

      /* Some error occurred. Most likely it's an OOM error but we don't
       * really care. Simply release all cache memory and disable caching
       */
      if (err)
        {
          /* Memory cleanup */
          svn_pool_destroy(pool);

          /* Document that we actually don't have a cache. */
          cache_settings.cache_size = 0;

          return svn_error_trace(err);
        }

      /* done */
      *cache_p = cache;
    }

  return SVN_NO_ERROR;
}