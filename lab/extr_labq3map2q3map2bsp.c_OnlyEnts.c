#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  LoadBSPFile (char*) ; 
 int /*<<< orphan*/  LoadMapFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LoadShaderInfo () ; 
 int /*<<< orphan*/  SetLightStyles () ; 
 int /*<<< orphan*/  SetModelNumbers () ; 
 int /*<<< orphan*/  Sys_Printf (char*) ; 
 int /*<<< orphan*/  UnparseEntities () ; 
 int /*<<< orphan*/  WriteBSPFile (char*) ; 
 int /*<<< orphan*/  name ; 
 scalar_t__ numBSPEntities ; 
 scalar_t__ numEntities ; 
 int /*<<< orphan*/  qfalse ; 
 char* source ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

void OnlyEnts( void ){
	char out[ 1024 ];


	/* note it */
	Sys_Printf( "--- OnlyEnts ---\n" );

	sprintf( out, "%s.bsp", source );
	LoadBSPFile( out );
	numEntities = 0;

	LoadShaderInfo();
	LoadMapFile( name, qfalse );
	SetModelNumbers();
	SetLightStyles();

	numBSPEntities = numEntities;
	UnparseEntities();

	WriteBSPFile( out );
}