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

char *
cgetcap(char *buf, const char *cap, int type)
{
	char *bp;
	const char *cp;

	bp = buf;
	for (;;) {
		/*
		 * Skip past the current capability field - it's either the
		 * name field if this is the first time through the loop, or
		 * the remainder of a field whose name failed to match cap.
		 */
		for (;;)
			if (*bp == '\0')
				return (NULL);
			else
				if (*bp++ == ':')
					break;

		/*
		 * Try to match (cap, type) in buf.
		 */
		for (cp = cap; *cp == *bp && *bp != '\0'; cp++, bp++)
			continue;
		if (*cp != '\0')
			continue;
		if (*bp == '@')
			return (NULL);
		if (type == ':') {
			if (*bp != '\0' && *bp != ':')
				continue;
			return(bp);
		}
		if (*bp != type)
			continue;
		bp++;
		return (*bp == '@' ? NULL : bp);
	}
	/* NOTREACHED */
}