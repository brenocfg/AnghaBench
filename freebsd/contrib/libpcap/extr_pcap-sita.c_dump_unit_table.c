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
struct TYPE_3__ {char* name; char* IOPname; struct TYPE_3__* next; } ;
typedef  TYPE_1__ iface_t ;
struct TYPE_4__ {char* ip; int fd; TYPE_1__* iface; } ;

/* Variables and functions */
 int MAX_CHASSIS ; 
 int MAX_GEOSLOT ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 TYPE_2__** units ; 

__attribute__((used)) static void dump_unit_table(void) {
	int		chassis, geoslot;
	iface_t	*p;

	printf("%c:%c %s %s\n", 'C', 'S', "fd", "IP Address");
	for (chassis = 0; chassis <= MAX_CHASSIS; chassis++) {
		for (geoslot = 0; geoslot <= MAX_GEOSLOT; geoslot++) {
			if (units[chassis][geoslot].ip != NULL)
				printf("%d:%d %2d %s\n", chassis, geoslot, units[chassis][geoslot].fd, units[chassis][geoslot].ip);
			p = units[chassis][geoslot].iface;
			while (p) {
				char *n = (p->name)			? p->name			: "";
				char *i = (p->IOPname)		? p->IOPname		: "";
				p = p->next;
				printf("   %12s    -> %12s\n", i, n);
			}
		}
	}
}