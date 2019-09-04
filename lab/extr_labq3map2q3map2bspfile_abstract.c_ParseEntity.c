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
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_5__ {struct TYPE_5__* next; } ;
typedef  TYPE_1__ epair_t ;
struct TYPE_6__ {TYPE_1__* epairs; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPAIR_STRCMP (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Error (char*) ; 
 int /*<<< orphan*/  GetToken (int /*<<< orphan*/ ) ; 
 size_t MAX_MAP_ENTITIES ; 
 TYPE_1__* ParseEPair () ; 
 TYPE_2__* entities ; 
 TYPE_2__* mapEnt ; 
 size_t numEntities ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  token ; 

qboolean ParseEntity( void ){
	epair_t     *e;


	/* dummy check */
	if ( !GetToken( qtrue ) ) {
		return qfalse;
	}
	if ( strcmp( token, "{" ) ) {
		Error( "ParseEntity: { not found" );
	}
	if ( numEntities == MAX_MAP_ENTITIES ) {
		Error( "numEntities == MAX_MAP_ENTITIES" );
	}

	/* create new entity */
	mapEnt = &entities[ numEntities ];
	numEntities++;

	/* parse */
	while ( 1 )
	{
		if ( !GetToken( qtrue ) ) {
			Error( "ParseEntity: EOF without closing brace" );
		}
		if ( !EPAIR_STRCMP( token, "}" ) ) {
			break;
		}
		e = ParseEPair();
		e->next = mapEnt->epairs;
		mapEnt->epairs = e;
	}

	/* return to sender */
	return qtrue;
}