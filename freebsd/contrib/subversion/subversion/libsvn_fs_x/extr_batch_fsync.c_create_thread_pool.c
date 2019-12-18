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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_THREADS ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  THREADPOOL_THREAD_IDLE_LIMIT ; 
 int /*<<< orphan*/  WRAP_APR_ERR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  apr_pool_pre_cleanup_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_thread_pool_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_thread_pool_idle_wait_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_thread_pool_threshold_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_pool ; 
 int /*<<< orphan*/  thread_pool_pre_cleanup ; 

__attribute__((used)) static svn_error_t *
create_thread_pool(void *baton,
                   apr_pool_t *owning_pool)
{
#if APR_HAS_THREADS
  /* The thread-pool must be allocated from a thread-safe pool.
     GLOBAL_POOL may be single-threaded, though. */
  apr_pool_t *pool = svn_pool_create(NULL);

  /* This thread pool will get cleaned up automatically when GLOBAL_POOL
     gets cleared.  No additional cleanup callback is needed. */
  WRAP_APR_ERR(apr_thread_pool_create(&thread_pool, 0, MAX_THREADS, pool),
               _("Can't create fsync thread pool in FSX"));

  /* Work around an APR bug:  The cleanup must happen in the pre-cleanup
     hook instead of the normal cleanup hook.  Otherwise, the sub-pools
     containing the thread objects would already be invalid. */
  apr_pool_pre_cleanup_register(pool, NULL, thread_pool_pre_cleanup);
  apr_pool_pre_cleanup_register(owning_pool, NULL, thread_pool_pre_cleanup);

  /* let idle threads linger for a while in case more requests are
     coming in */
  apr_thread_pool_idle_wait_set(thread_pool, THREADPOOL_THREAD_IDLE_LIMIT);

  /* don't queue requests unless we reached the worker thread limit */
  apr_thread_pool_threshold_set(thread_pool, 0);

#endif

  return SVN_NO_ERROR;
}