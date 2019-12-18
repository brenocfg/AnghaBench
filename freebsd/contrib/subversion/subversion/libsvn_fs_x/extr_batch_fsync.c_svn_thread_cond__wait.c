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
typedef  int /*<<< orphan*/  svn_thread_cond__t ;
typedef  int /*<<< orphan*/  svn_mutex__t ;
typedef  int /*<<< orphan*/  svn_error_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  WRAP_APR_ERR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  apr_thread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_mutex__get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
svn_thread_cond__wait(svn_thread_cond__t *cond,
                      svn_mutex__t *mutex)
{
#if APR_HAS_THREADS

  WRAP_APR_ERR(apr_thread_cond_wait(cond, svn_mutex__get(mutex)),
               _("Can't broadcast condition variable"));

#endif

  return SVN_NO_ERROR;
}