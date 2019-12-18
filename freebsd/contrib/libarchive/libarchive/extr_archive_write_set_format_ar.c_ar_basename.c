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
 int strlen (char const*) ; 

__attribute__((used)) static const char *
ar_basename(const char *path)
{
	const char *endp, *startp;

	endp = path + strlen(path) - 1;
	/*
	 * For filename with trailing slash(es), we return
	 * NULL indicating an error.
	 */
	if (*endp == '/')
		return (NULL);

	/* Find the start of the base */
	startp = endp;
	while (startp > path && *(startp - 1) != '/')
		startp--;
	
	return (startp);
}