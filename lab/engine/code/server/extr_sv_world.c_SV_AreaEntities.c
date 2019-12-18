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
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_3__ {int* list; int count; int maxcount; int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; } ;
typedef  TYPE_1__ areaParms_t ;

/* Variables and functions */
 int /*<<< orphan*/  SV_AreaEntities_r (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  sv_worldSectors ; 

int SV_AreaEntities( const vec3_t mins, const vec3_t maxs, int *entityList, int maxcount ) {
	areaParms_t		ap;

	ap.mins = mins;
	ap.maxs = maxs;
	ap.list = entityList;
	ap.count = 0;
	ap.maxcount = maxcount;

	SV_AreaEntities_r( sv_worldSectors, &ap );

	return ap.count;
}