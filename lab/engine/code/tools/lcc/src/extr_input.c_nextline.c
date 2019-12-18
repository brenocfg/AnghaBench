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
 char* cp ; 
 int /*<<< orphan*/  fillbuf () ; 
 char* limit ; 
 char* line ; 
 int /*<<< orphan*/  lineno ; 
 int /*<<< orphan*/  resynch () ; 

void nextline(void) {
	do {
		if (cp >= limit) {
			fillbuf();
			if (cp >= limit)
				cp = limit;
			if (cp == limit)
				return;
		} else {
			lineno++;
			for (line = (char *)cp; *cp==' ' || *cp=='\t'; cp++)
				;
			if (*cp == '#') {
				resynch();
				nextline();
			}
		}
	} while (*cp == '\n' && cp == limit);
}