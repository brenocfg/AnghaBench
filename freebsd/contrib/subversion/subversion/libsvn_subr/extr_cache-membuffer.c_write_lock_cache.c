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
struct TYPE_3__ {scalar_t__ lock; scalar_t__ allow_blocking_writes; } ;
typedef  TYPE_1__ svn_membuffer_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  scalar_t__ apr_status_t ;

/* Variables and functions */
 scalar_t__ APR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ SVN_LOCK_IS_BUSY (scalar_t__) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ apr_thread_rwlock_trywrlock (scalar_t__) ; 
 scalar_t__ apr_thread_rwlock_wrlock (scalar_t__) ; 
 int /*<<< orphan*/ * svn_error_wrap_apr (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_mutex__lock (scalar_t__) ; 

__attribute__((used)) static svn_error_t *
write_lock_cache(svn_membuffer_t *cache, svn_boolean_t *success)
{
#if (APR_HAS_THREADS && USE_SIMPLE_MUTEX)
  return svn_mutex__lock(cache->lock);
#elif (APR_HAS_THREADS && !USE_SIMPLE_MUTEX)
  if (cache->lock)
    {
      apr_status_t status;
      if (cache->allow_blocking_writes)
        {
          status = apr_thread_rwlock_wrlock(cache->lock);
        }
      else
        {
          status = apr_thread_rwlock_trywrlock(cache->lock);
          if (SVN_LOCK_IS_BUSY(status))
            {
              *success = FALSE;
              status = APR_SUCCESS;
            }
        }

      if (status)
        return svn_error_wrap_apr(status,
                                  _("Can't write-lock cache mutex"));
    }

  return SVN_NO_ERROR;
#else
  return SVN_NO_ERROR;
#endif
}