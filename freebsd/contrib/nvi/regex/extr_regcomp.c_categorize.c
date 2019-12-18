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
struct re_guts {int /*<<< orphan*/  ncategories; scalar_t__* categories; } ;
struct parse {scalar_t__ error; } ;
typedef  scalar_t__ cat_t ;

/* Variables and functions */
 int CHAR_MAX ; 
 int CHAR_MIN ; 
 scalar_t__ isinsets (struct re_guts*,int) ; 
 scalar_t__ samesets (struct re_guts*,int,int) ; 

__attribute__((used)) static void
categorize(struct parse *p, struct re_guts *g)
{
#ifdef notdef
	cat_t *cats = g->categories;
	int c;
	int c2;
	cat_t cat;

	/* avoid making error situations worse */
	if (p->error != 0)
		return;

	for (c = CHAR_MIN; c <= CHAR_MAX; c++)
		if (cats[c] == 0 && isinsets(g, c)) {
			cat = g->ncategories++;
			cats[c] = cat;
			for (c2 = c+1; c2 <= CHAR_MAX; c2++)
				if (cats[c2] == 0 && samesets(g, c, c2))
					cats[c2] = cat;
		}
#endif
}