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
struct _s_x {char const* s; int x; } ;

/* Variables and functions */

char const *
match_value(struct _s_x *p, int value)
{
	for (; p->s != NULL; p++)
		if (p->x == value)
			return p->s;
	return NULL;
}