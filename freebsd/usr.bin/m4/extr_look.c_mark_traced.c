#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ndptr ;
struct TYPE_5__ {int trace_flags; } ;

/* Variables and functions */
 int FLAG_NO_TRACE ; 
 int /*<<< orphan*/  TRACE_ALL ; 
 TYPE_1__* create_entry (char const*) ; 
 int /*<<< orphan*/  macros ; 
 TYPE_1__* ohash_first (int /*<<< orphan*/ *,unsigned int*) ; 
 TYPE_1__* ohash_next (int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  trace_flags ; 

void
mark_traced(const char *name, int on)
{
	ndptr p;
	unsigned int i;

	if (name == NULL) {
		if (on)
			trace_flags |= TRACE_ALL;
		else
			trace_flags &= ~TRACE_ALL;
		for (p = ohash_first(&macros, &i); p != NULL;
		    p = ohash_next(&macros, &i))
			p->trace_flags = FLAG_NO_TRACE;
	} else {
		p = create_entry(name);
		p->trace_flags = on;
	}
}