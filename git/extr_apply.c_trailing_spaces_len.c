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

__attribute__((used)) static size_t trailing_spaces_len(const char *line, size_t len)
{
	const char *p;

	/* Expected format: ' ' x (1 or more)  */
	if (!len || line[len - 1] != ' ')
		return 0;

	p = line + len;
	while (p != line) {
		p--;
		if (*p != ' ')
			return line + len - (p + 1);
	}

	/* All spaces! */
	return len;
}