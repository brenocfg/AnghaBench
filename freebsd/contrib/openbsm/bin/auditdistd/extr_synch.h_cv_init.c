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
typedef  int /*<<< orphan*/  pthread_condattr_t ;
typedef  int /*<<< orphan*/  pthread_cond_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pthread_condattr_destroy (int /*<<< orphan*/ *) ; 
 int pthread_condattr_init (int /*<<< orphan*/ *) ; 
 int pthread_condattr_setclock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void
cv_init(pthread_cond_t *cv)
{
	pthread_condattr_t attr;
	int error;

	error = pthread_condattr_init(&attr);
	PJDLOG_ASSERT(error == 0);
#ifdef HAVE_PTHREAD_CONDATTR_SETCLOCK
	error = pthread_condattr_setclock(&attr, CLOCK_MONOTONIC);
	PJDLOG_ASSERT(error == 0);
#endif
	error = pthread_cond_init(cv, &attr);
	PJDLOG_ASSERT(error == 0);
	error = pthread_condattr_destroy(&attr);
	PJDLOG_ASSERT(error == 0);
}