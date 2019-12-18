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
 int /*<<< orphan*/  git__isspace (unsigned char) ; 

__attribute__((used)) static size_t line_length_without_trailing_spaces(const char *line, size_t len)
{
	while (len) {
		unsigned char c = line[len - 1];
		if (!git__isspace(c))
			break;
		len--;
	}

	return len;
}