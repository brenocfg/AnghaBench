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
struct pthread {int dummy; } ;

/* Variables and functions */
 struct pthread* _get_curthread () ; 
 int /*<<< orphan*/  pshared_clean (void*,void*) ; 
 int /*<<< orphan*/  pshared_gc (struct pthread*) ; 
 void* pshared_remove (void*) ; 
 int /*<<< orphan*/  pshared_unlock (struct pthread*) ; 
 int /*<<< orphan*/  pshared_wlock (struct pthread*) ; 

void
__thr_pshared_destroy(void *key)
{
	struct pthread *curthread;
	void *val;

	curthread = _get_curthread();
	pshared_wlock(curthread);
	val = pshared_remove(key);
	pshared_unlock(curthread);
	pshared_clean(key, val);
	pshared_gc(curthread);
}