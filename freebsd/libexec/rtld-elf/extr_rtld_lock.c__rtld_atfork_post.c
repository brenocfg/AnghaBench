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
typedef  int /*<<< orphan*/  ls ;
struct TYPE_4__ {int lockstate; } ;
typedef  TYPE_1__ RtldLockState ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  lock_release (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  rtld_bind_lock ; 
 int /*<<< orphan*/  rtld_phdr_lock ; 

void
_rtld_atfork_post(int *locks)
{
	RtldLockState ls[2];

	if (locks == NULL)
		return;

	bzero(ls, sizeof(ls));
	ls[0].lockstate = locks[2];
	ls[1].lockstate = locks[0];
	lock_release(rtld_bind_lock, &ls[1]);
	lock_release(rtld_phdr_lock, &ls[0]);
}