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
struct object_entry {int dummy; } ;

/* Variables and functions */
 struct object_entry* DELTA_CHILD (struct object_entry*) ; 
 struct object_entry* DELTA_SIBLING (struct object_entry*) ; 

__attribute__((used)) static unsigned int check_delta_limit(struct object_entry *me, unsigned int n)
{
	struct object_entry *child = DELTA_CHILD(me);
	unsigned int m = n;
	while (child) {
		const unsigned int c = check_delta_limit(child, n + 1);
		if (m < c)
			m = c;
		child = DELTA_SIBLING(child);
	}
	return m;
}