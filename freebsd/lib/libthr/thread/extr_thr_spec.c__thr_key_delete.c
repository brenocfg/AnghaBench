#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pthread {int dummy; } ;
typedef  int pthread_key_t ;
struct TYPE_2__ {scalar_t__ allocated; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int PTHREAD_KEYS_MAX ; 
 int /*<<< orphan*/  THR_LOCK_ACQUIRE (struct pthread*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  THR_LOCK_RELEASE (struct pthread*,int /*<<< orphan*/ *) ; 
 struct pthread* _get_curthread () ; 
 int /*<<< orphan*/  _keytable_lock ; 
 TYPE_1__* _thread_keytable ; 

int
_thr_key_delete(pthread_key_t userkey)
{
	struct pthread *curthread;
	int key, ret;

	key = userkey - 1;
	if ((unsigned int)key >= PTHREAD_KEYS_MAX)
		return (EINVAL);
	curthread = _get_curthread();
	THR_LOCK_ACQUIRE(curthread, &_keytable_lock);
	if (_thread_keytable[key].allocated) {
		_thread_keytable[key].allocated = 0;
		ret = 0;
	} else {
		ret = EINVAL;
	}
	THR_LOCK_RELEASE(curthread, &_keytable_lock);
	return (ret);
}