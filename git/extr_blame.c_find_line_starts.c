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
 int /*<<< orphan*/  ALLOC_ARRAY (int*,int) ; 
 char* get_next_line (char const*,char const*) ; 

__attribute__((used)) static int find_line_starts(int **line_starts, const char *buf,
			    unsigned long len)
{
	const char *end = buf + len;
	const char *p;
	int *lineno;
	int num = 0;

	for (p = buf; p < end; p = get_next_line(p, end))
		num++;

	ALLOC_ARRAY(*line_starts, num + 1);
	lineno = *line_starts;

	for (p = buf; p < end; p = get_next_line(p, end))
		*lineno++ = p - buf;

	*lineno = len;

	return num;
}