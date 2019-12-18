#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* name; struct TYPE_3__* next; scalar_t__ IOPname; } ;
typedef  TYPE_1__ iface_t ;
struct TYPE_4__ {TYPE_1__* iface; int /*<<< orphan*/ * ip; } ;

/* Variables and functions */
 int MAX_CHASSIS ; 
 int MAX_GEOSLOT ; 
 TYPE_2__** units ; 

__attribute__((used)) static char *find_nth_interface_name(int n) {
	int		chassis, geoslot;
	iface_t	*p;
	char	*last_name = 0;

	if (n < 0) n = 0;												/* ensure we are working with a valid number */
	for (chassis = 0; chassis <= MAX_CHASSIS; chassis++) {			/* scan the table... */
		for (geoslot = 0; geoslot <= MAX_GEOSLOT; geoslot++) {
			if (units[chassis][geoslot].ip != NULL) {
				p = units[chassis][geoslot].iface;
				while (p) {											/* and all interfaces... */
					if (p->IOPname) last_name = p->name;			/* remembering the last name found */
					if (n-- == 0) return last_name;					/* and if we hit the instance requested */
					p = p->next;
				}
			}
		}
	}
											/* if we couldn't fine the selected entry */
	if (last_name)	return last_name;		/* ... but we did have at least one entry... return the last entry found */
	return "";								/* ... but if there wasn't any entry... return an empty string instead */
}