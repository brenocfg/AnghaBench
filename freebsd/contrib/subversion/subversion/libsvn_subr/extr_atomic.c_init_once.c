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
typedef  int /*<<< orphan*/  const svn_boolean_t ;
typedef  int svn_atomic_t ;
typedef  int /*<<< orphan*/  const (* init_func_t ) (int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  init_baton_t ;

/* Variables and functions */
 int APR_USEC_PER_SEC ; 
 int /*<<< orphan*/  const FALSE ; 
#define  SVN_ATOMIC_INITIALIZED 131 
#define  SVN_ATOMIC_INIT_FAILED 130 
#define  SVN_ATOMIC_START_INIT 129 
#define  SVN_ATOMIC_UNINITIALIZED 128 
 int /*<<< orphan*/  const TRUE ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  apr_sleep (int) ; 
 int svn_atomic_cas (int volatile*,int const,int const) ; 

__attribute__((used)) static svn_boolean_t
init_once(volatile svn_atomic_t *global_status,
          init_func_t init_func, init_baton_t *init_baton)
{
  /* !! Don't use localizable strings in this function, because these
     !! might cause deadlocks. This function can be used to initialize
     !! libraries that are used for generating error messages. */

  /* We have to call init_func exactly once.  Because APR
     doesn't have statically-initialized mutexes, we implement a poor
     man's spinlock using svn_atomic_cas. */

  svn_atomic_t status = svn_atomic_cas(global_status,
                                       SVN_ATOMIC_START_INIT,
                                       SVN_ATOMIC_UNINITIALIZED);

  for (;;)
    {
      switch (status)
        {
        case SVN_ATOMIC_UNINITIALIZED:
          {
            const svn_boolean_t result = init_func(init_baton);
            const svn_atomic_t init_state = (result
                                             ? SVN_ATOMIC_INITIALIZED
                                             : SVN_ATOMIC_INIT_FAILED);

            svn_atomic_cas(global_status, init_state,
                           SVN_ATOMIC_START_INIT);
            return result;
          }

        case SVN_ATOMIC_START_INIT:
          /* Wait for the init function to complete. */
          apr_sleep(APR_USEC_PER_SEC / 1000);
          status = svn_atomic_cas(global_status,
                                  SVN_ATOMIC_UNINITIALIZED,
                                  SVN_ATOMIC_UNINITIALIZED);
          continue;

        case SVN_ATOMIC_INIT_FAILED:
          return FALSE;

        case SVN_ATOMIC_INITIALIZED:
          return TRUE;

        default:
          /* Something went seriously wrong with the atomic operations. */
          abort();
        }
    }
}