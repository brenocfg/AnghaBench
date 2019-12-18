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

/* Variables and functions */
 scalar_t__ _pthread_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _pthread_self () ; 
 int /*<<< orphan*/  _thr_initial ; 

int
_thr_main_np(void)
{

	if (!_thr_initial)
		return (-1);
	else
		return (_pthread_equal(_pthread_self(), _thr_initial) ? 1 : 0);
}