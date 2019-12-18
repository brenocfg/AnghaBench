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
 char* strstr (char*,char*) ; 

__attribute__((used)) static void
reduce_path(char *fn)
{
	char *slash, *ptr;

	/* Reduce all "/+./" to "/" (just in case we've got "/./../" later */
	while ((slash = strstr(fn, "/./")) != NULL) {
		for (ptr = slash; ptr > fn && ptr[-1] == '/'; ptr--)
			;
		slash += 2;
		while (*slash)
			*++ptr = *++slash;
	}

	/* Now reduce all "/something/+../" to "/" */
	while ((slash = strstr(fn, "/../")) != NULL) {
		if (slash == fn)
			break;
		for (ptr = slash; ptr > fn && ptr[-1] == '/'; ptr--)
			;
		for (ptr--; ptr >= fn; ptr--)
			if (*ptr == '/')
				break;
		if (ptr < fn)
			break;
		slash += 3;
		while (*slash)
			*++ptr = *++slash;
	}
}