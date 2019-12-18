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
 int /*<<< orphan*/  logprintf (char*,...) ; 

__attribute__((used)) static void
hexdump(const char *p, const char *ref, size_t l, size_t offset)
{
	size_t i, j;
	char sep;

	if (p == NULL) {
		logprintf("(null)\n");
		return;
	}
	for(i=0; i < l; i+=16) {
		logprintf("%04x", (unsigned)(i + offset));
		sep = ' ';
		for (j = 0; j < 16 && i + j < l; j++) {
			if (ref != NULL && p[i + j] != ref[i + j])
				sep = '_';
			logprintf("%c%02x", sep, 0xff & (int)p[i+j]);
			if (ref != NULL && p[i + j] == ref[i + j])
				sep = ' ';
		}
		for (; j < 16; j++) {
			logprintf("%c  ", sep);
			sep = ' ';
		}
		logprintf("%c", sep);
		for (j=0; j < 16 && i + j < l; j++) {
			int c = p[i + j];
			if (c >= ' ' && c <= 126)
				logprintf("%c", c);
			else
				logprintf(".");
		}
		logprintf("\n");
	}
}