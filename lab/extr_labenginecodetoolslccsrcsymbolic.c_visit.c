#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int inst; TYPE_2__* next; } ;
struct TYPE_6__ {TYPE_1__ x; struct TYPE_6__** kids; } ;
typedef  TYPE_2__* Node ;

/* Variables and functions */
 TYPE_2__** tail ; 

__attribute__((used)) static int visit(Node p, int n) {
	if (p && p->x.inst == 0) {
		p->x.inst = ++n;
		n = visit(p->kids[0], n);
		n = visit(p->kids[1], n);
		*tail = p;
		tail = &p->x.next;
	}
	return n;
}