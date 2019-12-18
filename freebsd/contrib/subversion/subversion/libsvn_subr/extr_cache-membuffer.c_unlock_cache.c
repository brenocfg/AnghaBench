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
struct TYPE_3__ {scalar_t__ lock; } ;
typedef  TYPE_1__ svn_membuffer_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ apr_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ apr_thread_rwlock_unlock (scalar_t__) ; 
 int /*<<< orphan*/ * svn_error_wrap_apr (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_mutex__unlock (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
unlock_cache(svn_membuffer_t *cache, svn_error_t *err)
{
#if (APR_HAS_THREADS && USE_SIMPLE_MUTEX)
  return svn_mutex__unlock(cache->lock, err);
#elif (APR_HAS_THREADS && !USE_SIMPLE_MUTEX)
  if (cache->lock)
  {
    apr_status_t status = apr_thread_rwlock_unlock(cache->lock);
    if (err)
      return err;

    if (status)
      return svn_error_wrap_apr(status, _("Can't unlock cache mutex"));
  }

  return err;
#else
  return err;
#endif
}