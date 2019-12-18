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
struct segment {double m; double y; double x; } ;
struct gen_sc {int dummy; } ;

/* Variables and functions */
 double INFINITY ; 
 struct segment* LIST_NEXT (struct segment*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _next ; 
 struct segment* gsc_getentry (struct gen_sc*,double) ; 

__attribute__((used)) static int
gsc_add_seg(struct gen_sc *gsc, double x, double y, double d, double m)
{
	struct segment	*start, *end, *s;
	double		 x2;

	if (d == INFINITY)
		x2 = INFINITY;
	else
		x2 = x + d;
	start = gsc_getentry(gsc, x);
	end = gsc_getentry(gsc, x2);
	if (start == NULL || end == NULL)
		return (-1);

	for (s = start; s != end; s = LIST_NEXT(s, _next)) {
		s->m += m;
		s->y += y + (s->x - x) * m;
	}

	end = gsc_getentry(gsc, INFINITY);
	for (; s != end; s = LIST_NEXT(s, _next)) {
		s->y += m * d;
	}

	return (0);
}