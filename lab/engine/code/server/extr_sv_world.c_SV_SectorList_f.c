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
struct TYPE_4__ {TYPE_2__* entities; } ;
typedef  TYPE_1__ worldSector_t ;
struct TYPE_5__ {struct TYPE_5__* nextEntityInWorldSector; } ;
typedef  TYPE_2__ svEntity_t ;

/* Variables and functions */
 int AREA_NODES ; 
 int /*<<< orphan*/  Com_Printf (char*,int,int) ; 
 TYPE_1__* sv_worldSectors ; 

void SV_SectorList_f( void ) {
	int				i, c;
	worldSector_t	*sec;
	svEntity_t		*ent;

	for ( i = 0 ; i < AREA_NODES ; i++ ) {
		sec = &sv_worldSectors[i];

		c = 0;
		for ( ent = sec->entities ; ent ; ent = ent->nextEntityInWorldSector ) {
			c++;
		}
		Com_Printf( "sector %i: %i entities\n", i, c );
	}
}