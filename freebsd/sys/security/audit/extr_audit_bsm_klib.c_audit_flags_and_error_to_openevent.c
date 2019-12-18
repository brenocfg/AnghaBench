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
typedef  int /*<<< orphan*/  au_event_t ;
struct TYPE_3__ {int aoe_flags; int /*<<< orphan*/  aoe_event; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUE_OPEN ; 
 int O_CREAT ; 
 int O_RDONLY ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 TYPE_1__* aue_open ; 
 int nitems (TYPE_1__*) ; 

au_event_t
audit_flags_and_error_to_openevent(int oflags, int error)
{
	int i;

	/*
	 * Need to check only those flags we care about.
	 */
	oflags = oflags & (O_RDONLY | O_CREAT | O_TRUNC | O_RDWR | O_WRONLY);
	for (i = 0; i < nitems(aue_open); i++) {
		if (aue_open[i].aoe_flags == oflags)
			return (aue_open[i].aoe_event);
	}
	return (AUE_OPEN);
}