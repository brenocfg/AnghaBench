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
 size_t MAX_LINE ; 
 int /*<<< orphan*/  bcopy (char*,char*,size_t) ; 
 char* linebuf ; 
 size_t linelen ; 

int
get_line(char *buf, size_t *valid)
{
	size_t i;

	if (*valid > MAX_LINE)
		return (-1);

	/* Copy to linebuf while searching for a newline. */
	for (i = 0; i < *valid; i++) {
		linebuf[i] = buf[i];
		if (buf[i] == '\0')
			return (-1);
		if (buf[i] == '\n')
			break;
	}

	if (i == *valid) {
		/* No newline found. */
		linebuf[0] = '\0';
		linelen = 0;
		if (i < MAX_LINE)
			return (0);
		return (-1);
	}

	linelen = i + 1;
	linebuf[linelen] = '\0';
	*valid -= linelen;
	
	/* Move leftovers to the start. */
	if (*valid != 0)
		bcopy(buf + linelen, buf, *valid);

	return ((int)linelen);
}