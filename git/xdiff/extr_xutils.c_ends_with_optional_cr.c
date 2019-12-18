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

__attribute__((used)) static int ends_with_optional_cr(const char *l, long s, long i)
{
	int complete = s && l[s-1] == '\n';

	if (complete)
		s--;
	if (s == i)
		return 1;
	/* do not ignore CR at the end of an incomplete line */
	if (complete && s == i + 1 && l[i] == '\r')
		return 1;
	return 0;
}