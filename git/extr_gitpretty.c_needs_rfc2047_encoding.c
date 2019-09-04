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
 scalar_t__ non_ascii (int) ; 

__attribute__((used)) static int needs_rfc2047_encoding(const char *line, int len)
{
	int i;

	for (i = 0; i < len; i++) {
		int ch = line[i];
		if (non_ascii(ch) || ch == '\n')
			return 1;
		if ((i + 1 < len) && (ch == '=' && line[i+1] == '?'))
			return 1;
	}

	return 0;
}