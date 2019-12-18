#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {int type; char const* f; char const* s; int /*<<< orphan*/  tsc; void* td; } ;

/* Variables and functions */
 long atomic_fetchadd_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_cyclecount () ; 
 long nitems (TYPE_1__*) ; 
 int /*<<< orphan*/  nrecs ; 
 TYPE_1__* timestamps ; 

void
tslog(void * td, int type, const char * f, const char * s)
{
	uint64_t tsc = get_cyclecount();
	long pos;

	/* Grab a slot. */
	pos = atomic_fetchadd_long(&nrecs, 1);

	/* Store record. */
	if (pos < nitems(timestamps)) {
		timestamps[pos].td = td;
		timestamps[pos].type = type;
		timestamps[pos].f = f;
		timestamps[pos].s = s;
		timestamps[pos].tsc = tsc;
	}
}