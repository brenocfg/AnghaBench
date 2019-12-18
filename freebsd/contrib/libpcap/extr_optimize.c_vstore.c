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
struct stmt {int /*<<< orphan*/  code; } ;

/* Variables and functions */
 int /*<<< orphan*/  NOP ; 
 int VAL_UNKNOWN ; 

__attribute__((used)) static inline void
vstore(struct stmt *s, int *valp, int newval, int alter)
{
	if (alter && newval != VAL_UNKNOWN && *valp == newval)
		s->code = NOP;
	else
		*valp = newval;
}