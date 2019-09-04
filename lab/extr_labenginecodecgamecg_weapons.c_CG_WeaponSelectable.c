#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_6__ {TYPE_2__* snap; } ;
struct TYPE_4__ {int* stats; int /*<<< orphan*/ * ammo; } ;
struct TYPE_5__ {TYPE_1__ ps; } ;

/* Variables and functions */
 size_t STAT_WEAPONS ; 
 TYPE_3__ cg ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

__attribute__((used)) static qboolean CG_WeaponSelectable( int i ) {
	if ( !cg.snap->ps.ammo[i] ) {
		return qfalse;
	}
	if ( ! (cg.snap->ps.stats[ STAT_WEAPONS ] & ( 1 << i ) ) ) {
		return qfalse;
	}

	return qtrue;
}