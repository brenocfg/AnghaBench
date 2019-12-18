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
struct TYPE_2__ {long dwNumberOfProcessors; } ;

/* Variables and functions */
 TYPE_1__ SystemInfo ; 
 int /*<<< orphan*/  initialize_action () ; 

unsigned int
isc_os_ncpus(void) {
	long ncpus = 1;
	initialize_action();
	ncpus = SystemInfo.dwNumberOfProcessors;
	if (ncpus <= 0)
		ncpus = 1;

	return ((unsigned int)ncpus);
}