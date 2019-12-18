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
 char _POSIX_VDISABLE ; 
 char*** charnames ; 
 char** charvars ; 

void
setchars(void)
{
	int i;
	const char *p;

	for (i = 0; charnames[i]; i++) {
		p = *charnames[i];
		if (p && *p)
			*charvars[i] = *p;
		else
			*charvars[i] = _POSIX_VDISABLE;
	}
}