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
 int read (int,char*,int) ; 

__attribute__((used)) static char *
get_line(int fd)
{
	size_t i = 0;
	static char linebuf[512];

	/*
	 * This is certainly slow, but it avoids having to include
	 * stdio.h unnecessarily. Issue files should be small anyway.
	 */
	while (i < (sizeof linebuf - 3) && read(fd, linebuf+i, 1)==1) {
		if (linebuf[i] == '\n') {
			/* Don't rely on newline mode, assume raw */
			linebuf[i++] = '\r';
			linebuf[i++] = '\n';
			linebuf[i] = '\0';
			return linebuf;
		}
		++i;
	}
	linebuf[i] = '\0';
	return i ? linebuf : 0;
}