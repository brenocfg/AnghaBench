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
struct TYPE_4__ {scalar_t__ dlopened; } ;
typedef  int /*<<< orphan*/  RtldLockState ;
typedef  TYPE_1__ Obj_Entry ;

/* Variables and functions */
 int /*<<< orphan*/  _rtld_error (char*) ; 
 TYPE_1__* dlcheck (void*) ; 
 int /*<<< orphan*/  lock_release (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* obj_from_addr (void*) ; 
 int /*<<< orphan*/  rlock_acquire (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtld_bind_lock ; 

int
_rtld_is_dlopened(void *arg)
{
	Obj_Entry *obj;
	RtldLockState lockstate;
	int res;

	rlock_acquire(rtld_bind_lock, &lockstate);
	obj = dlcheck(arg);
	if (obj == NULL)
		obj = obj_from_addr(arg);
	if (obj == NULL) {
		_rtld_error("No shared object contains address");
		lock_release(rtld_bind_lock, &lockstate);
		return (-1);
	}
	res = obj->dlopened ? 1 : 0;
	lock_release(rtld_bind_lock, &lockstate);
	return (res);
}