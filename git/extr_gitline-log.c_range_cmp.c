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
struct range {scalar_t__ start; } ;

/* Variables and functions */

__attribute__((used)) static int range_cmp(const void *_r, const void *_s)
{
	const struct range *r = _r;
	const struct range *s = _s;

	/* this could be simply 'return r.start-s.start', but for the types */
	if (r->start == s->start)
		return 0;
	if (r->start < s->start)
		return -1;
	return 1;
}