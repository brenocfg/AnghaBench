#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int sc_col; TYPE_1__* sc_smap; } ;
typedef  TYPE_2__ VI_PRIVATE ;
struct TYPE_10__ {int cols; } ;
struct TYPE_8__ {int coff; int soff; } ;
typedef  TYPE_3__ SCR ;

/* Variables and functions */
 scalar_t__ O_ISSET (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  O_LEFTRIGHT ; 
 int /*<<< orphan*/  O_NUMBER ; 
 int O_NUMBER_LENGTH ; 
 TYPE_2__* VIP (TYPE_3__*) ; 

int
vs_column(SCR *sp, size_t *colp)
{
	VI_PRIVATE *vip;

	vip = VIP(sp);

	*colp = (O_ISSET(sp, O_LEFTRIGHT) ?
	    vip->sc_smap->coff : (vip->sc_smap->soff - 1) * sp->cols) +
	    vip->sc_col - (O_ISSET(sp, O_NUMBER) ? O_NUMBER_LENGTH : 0);
	return (0);
}