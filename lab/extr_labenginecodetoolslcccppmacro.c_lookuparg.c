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
struct TYPE_7__ {scalar_t__ type; scalar_t__ len; scalar_t__ t; } ;
typedef  TYPE_2__ Token ;
struct TYPE_8__ {TYPE_1__* ap; } ;
struct TYPE_6__ {TYPE_2__* bp; TYPE_2__* lp; } ;
typedef  TYPE_3__ Nlist ;

/* Variables and functions */
 scalar_t__ NAME ; 
 scalar_t__ strncmp (char*,char*,scalar_t__) ; 

int
lookuparg(Nlist *mac, Token *tp)
{
	Token *ap;

	if (tp->type!=NAME || mac->ap==NULL)
		return -1;
	for (ap=mac->ap->bp; ap<mac->ap->lp; ap++) {
		if (ap->len==tp->len && strncmp((char*)ap->t,(char*)tp->t,ap->len)==0)
			return ap - mac->ap->bp;
	}
	return -1;
}