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
struct TYPE_3__ {scalar_t__ offset; int /*<<< orphan*/ * freemask; } ;
typedef  TYPE_1__ Env ;

/* Variables and functions */
 size_t FREG ; 
 size_t IREG ; 
 int /*<<< orphan*/ * freemask ; 
 scalar_t__ maxoffset ; 
 scalar_t__ offset ; 

void blockend(Env *e) {
	if (offset > maxoffset)
		maxoffset = offset;
	offset = e->offset;
	freemask[IREG] = e->freemask[IREG];
	freemask[FREG] = e->freemask[FREG];
}