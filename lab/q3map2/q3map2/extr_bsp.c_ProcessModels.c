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
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_3__ {int /*<<< orphan*/ * patches; int /*<<< orphan*/ * brushes; } ;
typedef  TYPE_1__ entity_t ;

/* Variables and functions */
 int /*<<< orphan*/  BeginBSPFile () ; 
 int /*<<< orphan*/  CreateMapFogs () ; 
 int /*<<< orphan*/  EmitFogs () ; 
 int /*<<< orphan*/  ProcessSubModel () ; 
 int /*<<< orphan*/  ProcessWorldModel () ; 
 int /*<<< orphan*/  SYS_VRB ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* entities ; 
 size_t mapEntityNum ; 
 int /*<<< orphan*/  numBSPModels ; 
 size_t numEntities ; 
 int /*<<< orphan*/  verbose ; 
 int /*<<< orphan*/  verboseEntities ; 

void ProcessModels( void ){
	qboolean oldVerbose;
	entity_t    *entity;


	/* preserve -v setting */
	oldVerbose = verbose;

	/* start a new bsp */
	BeginBSPFile();

	/* create map fogs */
	CreateMapFogs();

	/* walk entity list */
	for ( mapEntityNum = 0; mapEntityNum < numEntities; mapEntityNum++ )
	{
		/* get entity */
		entity = &entities[ mapEntityNum ];
		if ( entity->brushes == NULL && entity->patches == NULL ) {
			continue;
		}

		/* process the model */
		Sys_FPrintf( SYS_VRB, "############### model %i ###############\n", numBSPModels );
		if ( mapEntityNum == 0 ) {
			ProcessWorldModel();
		}
		else{
			ProcessSubModel();
		}

		/* potentially turn off the deluge of text */
		verbose = verboseEntities;
	}

	/* restore -v setting */
	verbose = oldVerbose;

	/* write fogs */
	EmitFogs();
}