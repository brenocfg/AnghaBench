#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int button; int obutton; int dz; int dy; int dx; int flags; } ;
typedef  TYPE_1__ mousestatus_t ;
struct TYPE_8__ {int wmode; int* zmap; } ;
struct TYPE_7__ {int count; } ;

/* Variables and functions */
 int MOUSE_MAXBUTTON ; 
 int MOUSE_POSCHANGED ; 
#define  MOUSE_XAXIS 129 
#define  MOUSE_YAXIS 128 
 int* p2l ; 
 TYPE_3__ rodent ; 
 TYPE_2__* zstate ; 

__attribute__((used)) static void
r_map(mousestatus_t *act1, mousestatus_t *act2)
{
    register int pb;
    register int pbuttons;
    int lbuttons;

    pbuttons = act1->button;
    lbuttons = 0;

    act2->obutton = act2->button;
    if (pbuttons & rodent.wmode) {
	pbuttons &= ~rodent.wmode;
	act1->dz = act1->dy;
	act1->dx = 0;
	act1->dy = 0;
    }
    act2->dx = act1->dx;
    act2->dy = act1->dy;
    act2->dz = act1->dz;

    switch (rodent.zmap[0]) {
    case 0:	/* do nothing */
	break;
    case MOUSE_XAXIS:
	if (act1->dz != 0) {
	    act2->dx = act1->dz;
	    act2->dz = 0;
	}
	break;
    case MOUSE_YAXIS:
	if (act1->dz != 0) {
	    act2->dy = act1->dz;
	    act2->dz = 0;
	}
	break;
    default:	/* buttons */
	pbuttons &= ~(rodent.zmap[0] | rodent.zmap[1]
		    | rodent.zmap[2] | rodent.zmap[3]);
	if ((act1->dz < -1) && rodent.zmap[2]) {
	    pbuttons |= rodent.zmap[2];
	    zstate[2].count = 1;
	} else if (act1->dz < 0) {
	    pbuttons |= rodent.zmap[0];
	    zstate[0].count = 1;
	} else if ((act1->dz > 1) && rodent.zmap[3]) {
	    pbuttons |= rodent.zmap[3];
	    zstate[3].count = 1;
	} else if (act1->dz > 0) {
	    pbuttons |= rodent.zmap[1];
	    zstate[1].count = 1;
	}
	act2->dz = 0;
	break;
    }

    for (pb = 0; (pb < MOUSE_MAXBUTTON) && (pbuttons != 0); ++pb) {
	lbuttons |= (pbuttons & 1) ? p2l[pb] : 0;
	pbuttons >>= 1;
    }
    act2->button = lbuttons;

    act2->flags = ((act2->dx || act2->dy || act2->dz) ? MOUSE_POSCHANGED : 0)
	| (act2->obutton ^ act2->button);
}