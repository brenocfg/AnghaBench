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
typedef  int /*<<< orphan*/  pthread_mutex_t ;
typedef  int /*<<< orphan*/  mtctxres_t ;

/* Variables and functions */
 int /*<<< orphan*/  PTHREAD_MUTEX_INITIALIZER ; 
 scalar_t__ __res_init_ctx () ; 
 int /*<<< orphan*/  _mtctxres_init () ; 
 int /*<<< orphan*/  key ; 
 scalar_t__ mt_key_initialized ; 
 int /*<<< orphan*/ * pthread_getspecific (int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_main_np () ; 
 scalar_t__ pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sharedctx ; 

mtctxres_t *
___mtctxres(void) {
#ifdef DO_PTHREADS
	mtctxres_t	*mt;

#ifdef _LIBC
	if (pthread_main_np() != 0)
		return (&sharedctx);
#endif

	/*
	 * This if clause should only be executed if we are linking
	 * statically.  When linked dynamically _mtctxres_init() should
	 * be called at binding time due the #pragma above.
	 */
	if (!mt_key_initialized) {
		static pthread_mutex_t keylock = PTHREAD_MUTEX_INITIALIZER;
                if (pthread_mutex_lock(&keylock) == 0) {
			_mtctxres_init();
			(void) pthread_mutex_unlock(&keylock);
		}
	}

	/*
	 * If we have already been called in this thread return the existing
	 * context.  Otherwise recreat a new context and return it.  If
	 * that fails return a global context.
	 */
	if (mt_key_initialized) {
		if (((mt = pthread_getspecific(key)) != NULL) ||
		    (__res_init_ctx() == 0 &&
		     (mt = pthread_getspecific(key)) != NULL)) {
			return (mt);
		}
	}
#endif
	return (&sharedctx);
}