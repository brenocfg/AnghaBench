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
struct val_neg_zone {scalar_t__ dclass; int /*<<< orphan*/  labs; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int dname_canon_lab_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

int val_neg_zone_compare(const void* a, const void* b)
{
	struct val_neg_zone* x = (struct val_neg_zone*)a;
	struct val_neg_zone* y = (struct val_neg_zone*)b;
	int m;
	if(x->dclass != y->dclass) {
		if(x->dclass < y->dclass)
			return -1;
		return 1;
	}
	return dname_canon_lab_cmp(x->name, x->labs, y->name, y->labs, &m);
}