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
struct TYPE_3__ {scalar_t__ kind; struct TYPE_3__* prev; } ;
typedef  TYPE_1__* Code ;

/* Variables and functions */
 scalar_t__ Jump ; 
 scalar_t__ Label ; 
 int Start ; 
 scalar_t__ Switch ; 
 TYPE_1__* codelist ; 

int reachable(int kind) {

	if (kind > Start) {
		Code cp;
		for (cp = codelist; cp->kind < Label; )
			cp = cp->prev;
		if (cp->kind == Jump || cp->kind == Switch)
			return 0;
	}
	return 1;
}