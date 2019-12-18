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
typedef  size_t u_int ;
struct typetable {size_t tablesize; int nextarg; int /*<<< orphan*/ * table; scalar_t__ tablemax; int /*<<< orphan*/ * stattable; } ;

/* Variables and functions */
 size_t STATIC_ARG_TBL_SIZE ; 
 int /*<<< orphan*/  T_UNUSED ; 

__attribute__((used)) static inline void
inittypes(struct typetable *types)
{
	u_int n;

	types->table = types->stattable;
	types->tablesize = STATIC_ARG_TBL_SIZE;
	types->tablemax = 0; 
	types->nextarg = 1;
	for (n = 0; n < STATIC_ARG_TBL_SIZE; n++)
		types->table[n] = T_UNUSED;
}