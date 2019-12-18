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
typedef  int /*<<< orphan*/  qtime_t ;

/* Variables and functions */
 int /*<<< orphan*/  UI_REAL_TIME ; 
 int syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int trap_RealTime(qtime_t *qtime) {
	return syscall( UI_REAL_TIME, qtime );
}