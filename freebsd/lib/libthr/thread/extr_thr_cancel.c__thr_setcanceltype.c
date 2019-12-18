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
struct pthread {int cancel_async; } ;

/* Variables and functions */
 int EINVAL ; 
#define  PTHREAD_CANCEL_ASYNCHRONOUS 129 
#define  PTHREAD_CANCEL_DEFERRED 128 
 struct pthread* _get_curthread () ; 
 int /*<<< orphan*/  testcancel (struct pthread*) ; 

int
_thr_setcanceltype(int type, int *oldtype)
{
	struct pthread	*curthread = _get_curthread();
	int oldval;

	oldval = curthread->cancel_async;
	switch (type) {
	case PTHREAD_CANCEL_ASYNCHRONOUS:
		curthread->cancel_async = 1;
		testcancel(curthread);
		break;
	case PTHREAD_CANCEL_DEFERRED:
		curthread->cancel_async = 0;
		break;
	default:
		return (EINVAL);
	}

	if (oldtype) {
		*oldtype = oldval ? PTHREAD_CANCEL_ASYNCHRONOUS :
		 	PTHREAD_CANCEL_DEFERRED;
	}
	return (0);
}