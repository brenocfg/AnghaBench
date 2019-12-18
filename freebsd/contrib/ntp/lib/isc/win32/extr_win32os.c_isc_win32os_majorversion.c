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
struct TYPE_2__ {scalar_t__ dwMajorVersion; } ;

/* Variables and functions */
 int /*<<< orphan*/  initialize_action () ; 
 TYPE_1__ osVer ; 

unsigned int
isc_win32os_majorversion(void) {
	initialize_action();
	return ((unsigned int)osVer.dwMajorVersion);
}