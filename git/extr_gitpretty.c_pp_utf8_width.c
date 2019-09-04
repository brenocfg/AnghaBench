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
 int utf8_width (char const**,size_t*) ; 

__attribute__((used)) static int pp_utf8_width(const char *start, const char *end)
{
	int width = 0;
	size_t remain = end - start;

	while (remain) {
		int n = utf8_width(&start, &remain);
		if (n < 0 || !start)
			return -1;
		width += n;
	}
	return width;
}