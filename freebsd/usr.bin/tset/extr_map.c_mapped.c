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
struct TYPE_3__ {int conditional; char const* type; int /*<<< orphan*/  speed; int /*<<< orphan*/ * porttype; struct TYPE_3__* next; } ;
typedef  TYPE_1__ MAP ;

/* Variables and functions */
#define  EQ 132 
#define  GE 131 
#define  GT 130 
#define  LE 129 
#define  LT 128 
 int /*<<< orphan*/  Ospeed ; 
 TYPE_1__* maplist ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ *,char const*) ; 

const char *
mapped(const char *type)
{
	MAP *mapp;
	int match;

	match = 0;
	for (mapp = maplist; mapp; mapp = mapp->next)
		if (mapp->porttype == NULL || !strcmp(mapp->porttype, type)) {
			switch (mapp->conditional) {
			case 0:			/* No test specified. */
				match = 1;
				break;
			case EQ:
				match =	(Ospeed	== mapp->speed);
				break;
			case GE:
				match =	(Ospeed	>= mapp->speed);
				break;
			case GT:
				match =	(Ospeed	> mapp->speed);
				break;
			case LE:
				match =	(Ospeed	<= mapp->speed);
				break;
			case LT:
				match =	(Ospeed	< mapp->speed);
				break;
			}
			if (match)
				return (mapp->type);
		}
	/* No match found; return given type. */
	return (type);
}