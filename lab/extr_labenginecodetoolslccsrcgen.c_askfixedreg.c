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
struct TYPE_8__ {int set; int mask; } ;
struct TYPE_6__ {TYPE_3__* regnode; } ;
struct TYPE_7__ {TYPE_1__ x; } ;
typedef  TYPE_2__* Symbol ;
typedef  TYPE_3__* Regnode ;

/* Variables and functions */
 int* freemask ; 
 int* usedmask ; 

__attribute__((used)) static Symbol askfixedreg(Symbol s) {
	Regnode r = s->x.regnode;
	int n = r->set;

	if (r->mask&~freemask[n])
		return NULL;
	else {
		freemask[n] &= ~r->mask;
		usedmask[n] |=  r->mask;
		return s;
	}
}