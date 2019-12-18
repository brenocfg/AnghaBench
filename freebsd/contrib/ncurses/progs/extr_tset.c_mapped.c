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
struct TYPE_3__ {scalar_t__ porttype; int conditional; int speed; char const* type; struct TYPE_3__* next; } ;
typedef  TYPE_1__ MAP ;

/* Variables and functions */
#define  EQ 132 
 int FALSE ; 
#define  GE 131 
#define  GT 130 
#define  LE 129 
#define  LT 128 
 int TRUE ; 
 TYPE_1__* maplist ; 
 scalar_t__ ospeed ; 
 int /*<<< orphan*/  strcmp (scalar_t__,char const*) ; 

__attribute__((used)) static const char *
mapped(const char *type)
{
    MAP *mapp;
    int match;

    for (mapp = maplist; mapp; mapp = mapp->next)
	if (mapp->porttype == 0 || !strcmp(mapp->porttype, type)) {
	    switch (mapp->conditional) {
	    case 0:		/* No test specified. */
		match = TRUE;
		break;
	    case EQ:
		match = ((int) ospeed == mapp->speed);
		break;
	    case GE:
		match = ((int) ospeed >= mapp->speed);
		break;
	    case GT:
		match = ((int) ospeed > mapp->speed);
		break;
	    case LE:
		match = ((int) ospeed <= mapp->speed);
		break;
	    case LT:
		match = ((int) ospeed < mapp->speed);
		break;
	    default:
		match = FALSE;
	    }
	    if (match)
		return (mapp->type);
	}
    /* No match found; return given type. */
    return (type);
}