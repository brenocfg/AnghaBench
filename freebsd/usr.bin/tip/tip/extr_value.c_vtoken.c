#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int v_type; int /*<<< orphan*/  v_access; } ;
typedef  TYPE_1__ value_t ;

/* Variables and functions */
 TYPE_1__* NOVAL ; 
 int NUMBER ; 
 int /*<<< orphan*/  READ ; 
 scalar_t__ atoi (char*) ; 
 char* expand (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ vaccess (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vassign (TYPE_1__*,char*) ; 
 TYPE_1__* vlookup (char*) ; 
 int /*<<< orphan*/  vprint (TYPE_1__*) ; 

__attribute__((used)) static void
vtoken(char *s)
{
	value_t *p;
	char *cp;

	if ((cp = strchr(s, '='))) {
		*cp = '\0';
		if ((p = vlookup(s))) {
			cp++;
			if (p->v_type&NUMBER)
				vassign(p, (char *)(intptr_t)atoi(cp));
			else {
				if (strcmp(s, "record") == 0)
					cp = expand(cp);
				vassign(p, cp);
			}
			return;
		}
	} else if ((cp = strchr(s, '?'))) {
		*cp = '\0';
		if ((p = vlookup(s)) && vaccess(p->v_access, READ)) {
			vprint(p);
			return;
		}
	} else {
		if (*s != '!')
			p = vlookup(s);
		else
			p = vlookup(s+1);
		if (p != NOVAL) {
			vassign(p, s);
			return;
		}
	}
	printf("%s: unknown variable\r\n", s);
}