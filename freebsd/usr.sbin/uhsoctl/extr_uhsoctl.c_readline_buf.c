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

__attribute__((used)) static int
readline_buf(const char *s, const char *e, char *buf, size_t bufsz)
{
	int pos = 0;
	char *p = buf;

	for (; s < e; s++) {
		*p = *s;
		pos++;
		if (pos >= (bufsz - 1))
			break;
		if (*p++ == '\n')
			break;
	}
	*p = '\0';
	return (pos);
}