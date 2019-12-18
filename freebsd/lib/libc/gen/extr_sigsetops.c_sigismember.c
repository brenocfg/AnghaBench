#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* __bits; } ;
typedef  TYPE_1__ sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int _SIG_BIT (int) ; 
 int _SIG_MAXSIG ; 
 size_t _SIG_WORD (int) ; 
 int /*<<< orphan*/  errno ; 

int
sigismember(const sigset_t *set, int signo)
{

	if (signo <= 0 || signo > _SIG_MAXSIG) {
		errno = EINVAL;
		return (-1);
	}
	return ((set->__bits[_SIG_WORD(signo)] & _SIG_BIT(signo)) ? 1 : 0);
}