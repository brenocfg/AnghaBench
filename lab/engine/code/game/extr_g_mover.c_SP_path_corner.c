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
struct TYPE_5__ {int /*<<< orphan*/  origin; } ;
struct TYPE_6__ {TYPE_1__ s; int /*<<< orphan*/  targetname; } ;
typedef  TYPE_2__ gentity_t ;

/* Variables and functions */
 int /*<<< orphan*/  G_FreeEntity (TYPE_2__*) ; 
 int /*<<< orphan*/  G_Printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtos (int /*<<< orphan*/ ) ; 

void SP_path_corner( gentity_t *self ) {
	if ( !self->targetname ) {
		G_Printf ("path_corner with no targetname at %s\n", vtos(self->s.origin));
		G_FreeEntity( self );
		return;
	}
	// path corners don't need to be linked in
}