#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_thread_mutex_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_allocator_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_THREAD_MUTEX_DEFAULT ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  SVN_ALLOCATOR_RECOMMENDED_MAX_FREE ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT_NO_RETURN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abort_on_pool_failure (int /*<<< orphan*/ ) ; 
 scalar_t__ apr_allocator_create (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  apr_allocator_max_free_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_allocator_mutex_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_allocator_owner_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_pool_tag (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  apr_thread_mutex_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

apr_allocator_t *
svn_pool_create_allocator(svn_boolean_t thread_safe)
{
  apr_allocator_t *allocator;
  apr_pool_t *pool;

  /* create the allocator and limit it's internal free list to keep
   * memory usage in check */

  if (apr_allocator_create(&allocator))
    abort_on_pool_failure(EXIT_FAILURE);

  apr_allocator_max_free_set(allocator, SVN_ALLOCATOR_RECOMMENDED_MAX_FREE);

  /* create the root pool */

  pool = svn_pool_create_ex(NULL, allocator);
  apr_allocator_owner_set(allocator, pool);

#if APR_POOL_DEBUG
  apr_pool_tag (pool, "svn root pool");
#endif

  /* By default, allocators are *not* thread-safe. We must provide a mutex
   * if we want thread-safety for that mutex. */

#if APR_HAS_THREADS
  if (thread_safe)
    {
      apr_thread_mutex_t *mutex;
      apr_thread_mutex_create(&mutex, APR_THREAD_MUTEX_DEFAULT, pool);
      apr_allocator_mutex_set(allocator, mutex);
    }
#endif

  /* better safe than sorry */
  SVN_ERR_ASSERT_NO_RETURN(allocator != NULL);

  return allocator;
}