#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  v_access; scalar_t__ v_name; } ;
typedef  TYPE_1__ value_t ;

/* Variables and functions */
 int /*<<< orphan*/  READ ; 
 scalar_t__ col ; 
 scalar_t__ equal (char*,char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ vaccess (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* vinterp (char*,char) ; 
 int /*<<< orphan*/  vprint (TYPE_1__*) ; 
 TYPE_1__* vtable ; 
 int /*<<< orphan*/  vtoken (char*) ; 

void
vlex(char *s)
{
	value_t *p;
	char *cp;

	if (equal(s, "all")) {
		for (p = vtable; p->v_name; p++)
			if (vaccess(p->v_access, READ))
				vprint(p);
	} else {
		do {
			if ((cp = vinterp(s, ' ')))
				cp++;
			vtoken(s);
			s = cp;
		} while (s);
	}
	if (col > 0) {
		printf("\r\n");
		col = 0;
	}
}