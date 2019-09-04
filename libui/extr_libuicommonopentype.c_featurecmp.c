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
struct feature {scalar_t__ a; scalar_t__ b; scalar_t__ c; scalar_t__ d; } ;

/* Variables and functions */
 int intdiff (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int featurecmp(const void *a, const void *b)
{
	const struct feature *f = (const struct feature *) a;
	const struct feature *g = (const struct feature *) b;

	if (f->a != g->a)
		return intdiff(f->a, g->a);
	if (f->b != g->b)
		return intdiff(f->b, g->b);
	if (f->c != g->c)
		return intdiff(f->c, g->c);
	return intdiff(f->d, g->d);
}