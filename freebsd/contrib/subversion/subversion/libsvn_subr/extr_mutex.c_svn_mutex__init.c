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
struct TYPE_4__ {int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ svn_mutex__t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_THREAD_MUTEX_DEFAULT ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 scalar_t__ apr_thread_mutex_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_wrap_apr (scalar_t__,int /*<<< orphan*/ ) ; 

svn_error_t *
svn_mutex__init(svn_mutex__t **mutex_p,
                svn_boolean_t mutex_required,
                apr_pool_t *result_pool)
{
  /* always initialize the mutex pointer, even though it is not
     strictly necessary if APR_HAS_THREADS has not been set */
  *mutex_p = NULL;

  if (mutex_required)
    {
      svn_mutex__t *mutex = apr_pcalloc(result_pool, sizeof(*mutex));

#if APR_HAS_THREADS
      apr_status_t status =
          apr_thread_mutex_create(&mutex->mutex,
                                  APR_THREAD_MUTEX_DEFAULT,
                                  result_pool);
      if (status)
        return svn_error_wrap_apr(status, _("Can't create mutex"));
#endif

      *mutex_p = mutex;
    }

  return SVN_NO_ERROR;
}