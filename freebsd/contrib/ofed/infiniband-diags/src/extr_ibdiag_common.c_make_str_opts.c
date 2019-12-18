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
struct option {unsigned int has_arg; scalar_t__ val; scalar_t__ name; } ;

/* Variables and functions */

__attribute__((used)) static void make_str_opts(const struct option *o, char *p, unsigned size)
{
	unsigned i, n = 0;

	for (n = 0; o->name && n + 2 + o->has_arg < size; o++) {
		p[n++] = (char)o->val;
		for (i = 0; i < (unsigned)o->has_arg; i++)
			p[n++] = ':';
	}
	p[n] = '\0';
}