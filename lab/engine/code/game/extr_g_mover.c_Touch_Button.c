#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  trace_t ;
struct TYPE_7__ {scalar_t__ moverState; int /*<<< orphan*/  client; } ;
typedef  TYPE_1__ gentity_t ;

/* Variables and functions */
 scalar_t__ MOVER_POS1 ; 
 int /*<<< orphan*/  Use_BinaryMover (TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 

void Touch_Button(gentity_t *ent, gentity_t *other, trace_t *trace ) {
	if ( !other->client ) {
		return;
	}

	if ( ent->moverState == MOVER_POS1 ) {
		Use_BinaryMover( ent, other, other );
	}
}