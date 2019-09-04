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
 int /*<<< orphan*/  printf (char*,...) ; 

void git__hexdump(const char *buffer, size_t len)
{
	static const size_t LINE_WIDTH = 16;

	size_t line_count, last_line, i, j;
	const char *line;

	line_count = (len / LINE_WIDTH);
	last_line = (len % LINE_WIDTH);

	for (i = 0; i < line_count; ++i) {
		line = buffer + (i * LINE_WIDTH);
		for (j = 0; j < LINE_WIDTH; ++j, ++line)
			printf("%02X ", (unsigned char)*line & 0xFF);

		printf("| ");

		line = buffer + (i * LINE_WIDTH);
		for (j = 0; j < LINE_WIDTH; ++j, ++line)
			printf("%c", (*line >= 32 && *line <= 126) ? *line : '.');

		printf("\n");
	}

	if (last_line > 0) {

		line = buffer + (line_count * LINE_WIDTH);
		for (j = 0; j < last_line; ++j, ++line)
			printf("%02X ", (unsigned char)*line & 0xFF);

		for (j = 0; j < (LINE_WIDTH - last_line); ++j)
			printf("	");

		printf("| ");

		line = buffer + (line_count * LINE_WIDTH);
		for (j = 0; j < last_line; ++j, ++line)
			printf("%c", (*line >= 32 && *line <= 126) ? *line : '.');

		printf("\n");
	}

	printf("\n");
}