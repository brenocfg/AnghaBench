#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  (* local ) (TYPE_1__*) ;} ;
struct TYPE_6__ {int defined; } ;
typedef  TYPE_1__* Symbol ;

/* Variables and functions */
 TYPE_5__* IR ; 
 int /*<<< orphan*/  btot (int,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 TYPE_1__* temporary (int,int /*<<< orphan*/ ) ; 

Symbol newtemp(int sclass, int tc, int size) {
	Symbol p = temporary(sclass, btot(tc, size));

	(*IR->local)(p);
	p->defined = 1;
	return p;
}