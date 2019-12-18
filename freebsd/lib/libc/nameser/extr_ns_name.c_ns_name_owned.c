#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ns_namemap_ct ;
struct TYPE_4__ {scalar_t__ len; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ strncasecmp (char const*,char const*,scalar_t__) ; 

int
ns_name_owned(ns_namemap_ct a, int an, ns_namemap_ct b, int bn) {
	/* If A is shorter, it cannot be owned by B. */
	if (an < bn)
		return (0);

	/* If they are unequal before the length of the shorter, A cannot... */
	while (bn > 0) {
		if (a->len != b->len ||
		    strncasecmp((const char *) a->base,
				(const char *) b->base, a->len) != 0)
			return (0);
		a++, an--;
		b++, bn--;
	}

	/* A might be longer or not, but either way, B owns it. */
	return (1);
}