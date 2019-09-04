#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_4__ {scalar_t__ inuse; } ;
typedef  TYPE_1__ gentity_t ;
struct TYPE_5__ {int num_entities; } ;

/* Variables and functions */
 int ENTITYNUM_MAX_NORMAL ; 
 size_t MAX_CLIENTS ; 
 TYPE_1__* g_entities ; 
 TYPE_2__ level ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

qboolean G_EntitiesFree( void ) {
	int			i;
	gentity_t	*e;

	if ( level.num_entities < ENTITYNUM_MAX_NORMAL ) {
		// can open a new slot if needed
		return qtrue;
	}

	e = &g_entities[MAX_CLIENTS];
	for ( i = MAX_CLIENTS; i < level.num_entities; i++, e++) {
		if ( e->inuse ) {
			continue;
		}
		// slot available
		return qtrue;
	}
	return qfalse;
}