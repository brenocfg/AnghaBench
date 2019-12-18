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
struct TYPE_3__ {struct TYPE_3__* next; int /*<<< orphan*/  name; int /*<<< orphan*/  goterror; } ;
typedef  TYPE_1__ prog_t ;

/* Variables and functions */
 int /*<<< orphan*/  infilename ; 
 TYPE_1__* progs ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
remove_error_progs(void)
{
	prog_t *p1, *p2;

	p1 = NULL; p2 = progs;
	while (p2 != NULL) {
		if (!p2->goterror)
			p1 = p2, p2 = p2->next;
		else {
			/* delete it from linked list */
			warnx("%s: %s: ignoring program because of errors",
			    infilename, p2->name);
			if (p1)
				p1->next = p2->next;
			else
				progs = p2->next;
			p2 = p2->next;
		}
	}
}