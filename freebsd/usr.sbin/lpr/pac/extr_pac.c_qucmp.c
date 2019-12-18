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
struct hent {scalar_t__ h_feetpages; int /*<<< orphan*/  h_name; } ;

/* Variables and functions */
 scalar_t__ reverse ; 
 scalar_t__ sort ; 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qucmp(const void *a, const void *b)
{
	register const struct hent *h1, *h2;
	register int r;

	h1 = *(const struct hent * const *)a;
	h2 = *(const struct hent * const *)b;
	if (sort)
		r = h1->h_feetpages < h2->h_feetpages ?
		    -1 : h1->h_feetpages > h2->h_feetpages;
	else
		r = strcmp(h1->h_name, h2->h_name);
	return(reverse ? -r : r);
}