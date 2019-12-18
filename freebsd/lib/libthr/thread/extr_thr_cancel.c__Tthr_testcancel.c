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
 int /*<<< orphan*/  _thr_check_init () ; 
 int /*<<< orphan*/  testcancel (struct pthread*) ; 

void
_Tthr_testcancel(void)
{
	struct pthread *curthread;

	_thr_check_init();
	curthread = _get_curthread();
	testcancel(curthread);
}