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
 size_t autostart ; 
 size_t autostop ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 scalar_t__ isdigit (unsigned char) ; 
 size_t maxval ; 
 int /*<<< orphan*/  memset (char*,char,size_t) ; 
 int /*<<< orphan*/  needpos (size_t) ; 
 char* positions ; 
 char* strsep (char**,char*) ; 
 size_t strtol (char*,char**,int) ; 

__attribute__((used)) static void
get_list(char *list)
{
	size_t setautostart, start, stop;
	char *pos;
	char *p;

	/*
	 * set a byte in the positions array to indicate if a field or
	 * column is to be selected; use +1, it's 1-based, not 0-based.
	 * Numbers and number ranges may be overlapping, repeated, and in
	 * any order. We handle "-3-5" although there's no real reason to.
	 */
	for (; (p = strsep(&list, ", \t")) != NULL;) {
		setautostart = start = stop = 0;
		if (*p == '-') {
			++p;
			setautostart = 1;
		}
		if (isdigit((unsigned char)*p)) {
			start = stop = strtol(p, &p, 10);
			if (setautostart && start > autostart)
				autostart = start;
		}
		if (*p == '-') {
			if (isdigit((unsigned char)p[1]))
				stop = strtol(p + 1, &p, 10);
			if (*p == '-') {
				++p;
				if (!autostop || autostop > stop)
					autostop = stop;
			}
		}
		if (*p)
			errx(1, "[-bcf] list: illegal list value");
		if (!stop || !start)
			errx(1, "[-bcf] list: values may not include zero");
		if (maxval < stop) {
			maxval = stop;
			needpos(maxval + 1);
		}
		for (pos = positions + start; start++ <= stop; *pos++ = 1);
	}

	/* overlapping ranges */
	if (autostop && maxval > autostop) {
		maxval = autostop;
		needpos(maxval + 1);
	}

	/* reversed range with autostart */
	if (maxval < autostart) {
		maxval = autostart;
		needpos(maxval + 1);
	}

	/* set autostart */
	if (autostart)
		memset(positions + 1, '1', autostart);
}