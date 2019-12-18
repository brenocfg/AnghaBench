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
struct local_zone {scalar_t__ dclass; int /*<<< orphan*/  namelabs; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int dname_lab_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

int 
local_zone_cmp(const void* z1, const void* z2)
{
	/* first sort on class, so that hierarchy can be maintained within
	 * a class */
	struct local_zone* a = (struct local_zone*)z1;
	struct local_zone* b = (struct local_zone*)z2;
	int m;
	if(a->dclass != b->dclass) {
		if(a->dclass < b->dclass)
			return -1;
		return 1;
	}
	return dname_lab_cmp(a->name, a->namelabs, b->name, b->namelabs, &m);
}