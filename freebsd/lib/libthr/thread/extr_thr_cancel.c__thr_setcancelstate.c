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
struct pthread {int cancel_enable; int /*<<< orphan*/  cancel_async; } ;

/* Variables and functions */
 int EINVAL ; 
#define  PTHREAD_CANCEL_DISABLE 129 
#define  PTHREAD_CANCEL_ENABLE 128 
 struct pthread* _get_curthread () ; 
 int /*<<< orphan*/  testcancel (struct pthread*) ; 

int
_thr_setcancelstate(int state, int *oldstate)
{
	struct pthread *curthread = _get_curthread();
	int oldval;

	oldval = curthread->cancel_enable;
	switch (state) {
	case PTHREAD_CANCEL_DISABLE:
		curthread->cancel_enable = 0;
		break;
	case PTHREAD_CANCEL_ENABLE:
		curthread->cancel_enable = 1;
		if (curthread->cancel_async)
			testcancel(curthread);
		break;
	default:
		return (EINVAL);
	}

	if (oldstate) {
		*oldstate = oldval ? PTHREAD_CANCEL_ENABLE :
			PTHREAD_CANCEL_DISABLE;
	}
	return (0);
}