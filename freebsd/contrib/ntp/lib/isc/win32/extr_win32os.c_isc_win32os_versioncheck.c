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
 int /*<<< orphan*/  initialize_action () ; 
 unsigned int isc_win32os_majorversion () ; 
 unsigned int isc_win32os_minorversion () ; 
 unsigned int isc_win32os_servicepackmajor () ; 
 unsigned int isc_win32os_servicepackminor () ; 

int
isc_win32os_versioncheck(unsigned int major, unsigned int minor,
		     unsigned int spmajor, unsigned int spminor) {

	initialize_action();

	if (major < isc_win32os_majorversion())
		return (1);
	if (major > isc_win32os_majorversion())
		return (-1);
	if (minor < isc_win32os_minorversion())
		return (1);
	if (minor > isc_win32os_minorversion())
		return (-1);
	if (spmajor < isc_win32os_servicepackmajor())
		return (1);
	if (spmajor > isc_win32os_servicepackmajor())
		return (-1);
	if (spminor < isc_win32os_servicepackminor())
		return (1);
	if (spminor > isc_win32os_servicepackminor())
		return (-1);

	/* Exact */
	return (0);
}