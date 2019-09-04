#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__** syms; } ;
struct TYPE_5__ {scalar_t__ wildcard; } ;
struct TYPE_6__ {TYPE_1__ x; } ;
typedef  TYPE_3__* Node ;

/* Variables and functions */
 int LBURG_MAX ; 
 size_t RX ; 

int notarget(Node p) {
	return p->syms[RX]->x.wildcard ? 0 : LBURG_MAX;
}