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
typedef  int wchar_t ;

/* Variables and functions */
 int /*<<< orphan*/  logprintf (char*,...) ; 

__attribute__((used)) static void
wcsdump(const char *e, const wchar_t *w)
{
	logprintf("      %s = ", e);
	if (w == NULL) {
		logprintf("(null)");
		return;
	}
	logprintf("\"");
	while (*w != L'\0') {
		unsigned int c = *w++;
		if (c >= 32 && c < 127)
			logprintf("%c", c);
		else if (c < 256)
			logprintf("\\x%02X", c);
		else if (c < 0x10000)
			logprintf("\\u%04X", c);
		else
			logprintf("\\U%08X", c);
	}
	logprintf("\"\n");
}