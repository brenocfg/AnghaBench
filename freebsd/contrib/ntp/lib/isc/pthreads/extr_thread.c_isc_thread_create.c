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
typedef  int /*<<< orphan*/  pthread_attr_t ;
typedef  int /*<<< orphan*/  isc_threadfunc_t ;
typedef  int /*<<< orphan*/  isc_threadarg_t ;
typedef  int /*<<< orphan*/  isc_thread_t ;
typedef  int /*<<< orphan*/  isc_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  ISC_R_UNEXPECTED ; 
 int /*<<< orphan*/  PTHREAD_SCOPE_SYSTEM ; 
 size_t THREAD_MINSTACKSIZE ; 
 int /*<<< orphan*/  pthread_attr_destroy (int /*<<< orphan*/ *) ; 
 int pthread_attr_getstacksize (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  pthread_attr_init (int /*<<< orphan*/ *) ; 
 int pthread_attr_setscope (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pthread_attr_setstacksize (int /*<<< orphan*/ *,size_t) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

isc_result_t
isc_thread_create(isc_threadfunc_t func, isc_threadarg_t arg,
		  isc_thread_t *thread)
{
	pthread_attr_t attr;
	size_t stacksize;
	int ret;

	pthread_attr_init(&attr);

#if defined(HAVE_PTHREAD_ATTR_GETSTACKSIZE) && \
    defined(HAVE_PTHREAD_ATTR_SETSTACKSIZE)
	ret = pthread_attr_getstacksize(&attr, &stacksize);
	if (ret != 0)
		return (ISC_R_UNEXPECTED);

	if (stacksize < THREAD_MINSTACKSIZE) {
		ret = pthread_attr_setstacksize(&attr, THREAD_MINSTACKSIZE);
		if (ret != 0)
			return (ISC_R_UNEXPECTED);
	}
#endif

#if defined(PTHREAD_SCOPE_SYSTEM) && defined(NEED_PTHREAD_SCOPE_SYSTEM)
	ret = pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
	if (ret != 0)
		return (ISC_R_UNEXPECTED);
#endif

	ret = pthread_create(thread, &attr, func, arg);
	if (ret != 0)
		return (ISC_R_UNEXPECTED);

	pthread_attr_destroy(&attr);

	return (ISC_R_SUCCESS);
}