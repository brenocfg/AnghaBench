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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int _SIG_MAXSIG ; 
 TYPE_1__* __libc_sigaction_slot (int) ; 
 int /*<<< orphan*/  _thr_rwl_rdlock (int /*<<< orphan*/ *) ; 

void
_thr_signal_prefork(void)
{
	int i;

	for (i = 1; i <= _SIG_MAXSIG; ++i)
		_thr_rwl_rdlock(&__libc_sigaction_slot(i)->lock);
}