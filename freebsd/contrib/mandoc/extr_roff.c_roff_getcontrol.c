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
struct roff {char control; } ;

/* Variables and functions */

int
roff_getcontrol(const struct roff *r, const char *cp, int *ppos)
{
	int		pos;

	pos = *ppos;

	if (r->control != '\0' && cp[pos] == r->control)
		pos++;
	else if (r->control != '\0')
		return 0;
	else if ('\\' == cp[pos] && '.' == cp[pos + 1])
		pos += 2;
	else if ('.' == cp[pos] || '\'' == cp[pos])
		pos++;
	else
		return 0;

	while (' ' == cp[pos] || '\t' == cp[pos])
		pos++;

	*ppos = pos;
	return 1;
}