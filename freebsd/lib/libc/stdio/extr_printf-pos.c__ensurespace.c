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
struct typetable {scalar_t__ nextarg; scalar_t__ tablesize; scalar_t__ tablemax; } ;

/* Variables and functions */
 scalar_t__ __grow_type_table (struct typetable*) ; 

__attribute__((used)) static inline int
_ensurespace(struct typetable *types)
{

	if (types->nextarg >= types->tablesize) {
		if (__grow_type_table(types))
			return (-1);
	}
	if (types->nextarg > types->tablemax)
		types->tablemax = types->nextarg;
	return (0);
}