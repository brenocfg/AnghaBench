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

__attribute__((used)) static void
undo_glob_escape(char *s)
{
	size_t i, j;

	for (i = j = 0;;) {
		if (s[i] == '\0') {
			s[j] = '\0';
			return;
		}
		if (s[i] != '\\') {
			s[j++] = s[i++];
			continue;
		}
		/* s[i] == '\\' */
		++i;
		switch (s[i]) {
		case '?':
		case '[':
		case '*':
		case '\\':
			s[j++] = s[i++];
			break;
		case '\0':
			s[j++] = '\\';
			s[j] = '\0';
			return;
		default:
			s[j++] = '\\';
			s[j++] = s[i++];
			break;
		}
	}
}