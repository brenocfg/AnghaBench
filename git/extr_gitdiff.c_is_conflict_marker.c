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
 int /*<<< orphan*/  isspace (char const) ; 

__attribute__((used)) static int is_conflict_marker(const char *line, int marker_size, unsigned long len)
{
	char firstchar;
	int cnt;

	if (len < marker_size + 1)
		return 0;
	firstchar = line[0];
	switch (firstchar) {
	case '=': case '>': case '<': case '|':
		break;
	default:
		return 0;
	}
	for (cnt = 1; cnt < marker_size; cnt++)
		if (line[cnt] != firstchar)
			return 0;
	/* line[1] thru line[marker_size-1] are same as firstchar */
	if (len < marker_size + 1 || !isspace(line[marker_size]))
		return 0;
	return 1;
}