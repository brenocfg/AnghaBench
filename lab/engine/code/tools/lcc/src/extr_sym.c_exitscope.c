#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ level; struct TYPE_6__* previous; TYPE_1__* all; } ;
struct TYPE_5__ {scalar_t__ level; struct TYPE_5__* previous; } ;
struct TYPE_4__ {scalar_t__ scope; struct TYPE_4__* up; } ;
typedef  TYPE_1__* Symbol ;

/* Variables and functions */
 int Aflag ; 
 scalar_t__ GLOBAL ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_3__* identifiers ; 
 scalar_t__ level ; 
 int /*<<< orphan*/  rmtypes (scalar_t__) ; 
 TYPE_2__* types ; 
 int /*<<< orphan*/  warning (char*) ; 

void exitscope(void) {
	rmtypes(level);
	if (types->level == level)
		types = types->previous;
	if (identifiers->level == level) {
		if (Aflag >= 2) {
			int n = 0;
			Symbol p;
			for (p = identifiers->all; p && p->scope == level; p = p->up)
				if (++n > 127) {
					warning("more than 127 identifiers declared in a block\n");
					break;
				}
		}
		identifiers = identifiers->previous;
	}
	assert(level >= GLOBAL);
	--level;
}