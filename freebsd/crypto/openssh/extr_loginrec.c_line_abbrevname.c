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
 int /*<<< orphan*/  memset (char*,char,int) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 

char *
line_abbrevname(char *dst, const char *src, int dstsize)
{
	size_t len;

	memset(dst, '\0', dstsize);

	/* Always skip prefix if present */
	if (strncmp(src, "/dev/", 5) == 0)
		src += 5;

#ifdef WITH_ABBREV_NO_TTY
	if (strncmp(src, "tty", 3) == 0)
		src += 3;
#endif

	len = strlen(src);

	if (len > 0) {
		if (((int)len - dstsize) > 0)
			src +=  ((int)len - dstsize);

		/* note: _don't_ change this to strlcpy */
		strncpy(dst, src, (size_t)dstsize);
	}

	return (dst);
}