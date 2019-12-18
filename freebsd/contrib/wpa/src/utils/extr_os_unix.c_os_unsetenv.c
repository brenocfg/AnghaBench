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
 int unsetenv (char const*) ; 

int os_unsetenv(const char *name)
{
#if defined(__FreeBSD__) || defined(__NetBSD__) || defined(__APPLE__) || \
    defined(__OpenBSD__)
	unsetenv(name);
	return 0;
#else
	return unsetenv(name);
#endif
}