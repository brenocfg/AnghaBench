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
struct trust_anchor {scalar_t__ dclass; int /*<<< orphan*/  namelabs; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int dname_lab_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

int
anchor_cmp(const void* k1, const void* k2)
{
	int m;
	struct trust_anchor* n1 = (struct trust_anchor*)k1;
	struct trust_anchor* n2 = (struct trust_anchor*)k2;
	/* no need to ntohs(class) because sort order is irrelevant */
	if(n1->dclass != n2->dclass) {
		if(n1->dclass < n2->dclass)
			return -1;
		return 1;
	}
	return dname_lab_cmp(n1->name, n1->namelabs, n2->name, n2->namelabs, 
		&m);
}