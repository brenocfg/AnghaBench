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
struct types {scalar_t__ t_name; int t_type; int /*<<< orphan*/  t_mode; } ;

/* Variables and functions */
 int COMPLETE ; 
 int TYPE_I ; 
 int TYPE_L ; 
 char* bytename ; 
 int command (char*,int /*<<< orphan*/ ,...) ; 
 int curtype ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 struct types* types ; 
 int verbose ; 

void
changetype(int newtype, int show)
{
	struct types *p;
	int comret, oldverbose = verbose;

	if (newtype == 0)
		newtype = TYPE_I;
	if (newtype == curtype)
		return;
	if (debug == 0 && show == 0)
		verbose = 0;
	for (p = types; p->t_name; p++)
		if (newtype == p->t_type)
			break;
	if (p->t_name == 0) {
		printf("ftp: internal error: unknown type %d\n", newtype);
		return;
	}
	if (newtype == TYPE_L && bytename[0] != '\0')
		comret = command("TYPE %s %s", p->t_mode, bytename);
	else
		comret = command("TYPE %s", p->t_mode);
	if (comret == COMPLETE)
		curtype = newtype;
	verbose = oldverbose;
}