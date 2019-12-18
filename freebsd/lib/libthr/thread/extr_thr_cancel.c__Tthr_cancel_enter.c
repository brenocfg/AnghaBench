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
 int /*<<< orphan*/  _get_curthread () ; 
 int /*<<< orphan*/  _thr_cancel_enter2 (int /*<<< orphan*/ ,int) ; 

void
_Tthr_cancel_enter(int maycancel)
{
	_thr_cancel_enter2(_get_curthread(), maycancel);
}