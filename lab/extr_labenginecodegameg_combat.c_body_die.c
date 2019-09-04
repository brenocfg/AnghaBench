#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ health; } ;
typedef  TYPE_1__ gentity_t ;
struct TYPE_8__ {int /*<<< orphan*/  integer; } ;

/* Variables and functions */
 scalar_t__ GIB_HEALTH ; 
 int /*<<< orphan*/  GibEntity (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_2__ g_blood ; 

void body_die( gentity_t *self, gentity_t *inflictor, gentity_t *attacker, int damage, int meansOfDeath ) {
	if ( self->health > GIB_HEALTH ) {
		return;
	}
	if ( !g_blood.integer ) {
		self->health = GIB_HEALTH+1;
		return;
	}

	GibEntity( self, 0 );
}