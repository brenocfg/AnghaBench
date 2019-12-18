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
struct TYPE_4__ {int surfaceFlags; int contentFlags; char* damageShader; int /*<<< orphan*/  shader; } ;
typedef  TYPE_1__ shaderInfo_t ;
struct TYPE_5__ {int surfaceFlags; int contentFlags; int /*<<< orphan*/  shader; } ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*) ; 
 int MAX_MAP_SHADERS ; 
 int /*<<< orphan*/  Q_stricmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_VRB ; 
 TYPE_1__* ShaderInfoForShader (char const*) ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* bspShaders ; 
 int numBSPShaders ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 

int EmitShader( const char *shader, int *contentFlags, int *surfaceFlags ){
	int i;
	shaderInfo_t    *si;


	/* handle special cases */
	if ( shader == NULL ) {
		shader = "noshader";
	}

	/* try to find an existing shader */
	for ( i = 0; i < numBSPShaders; i++ )
	{
		/* ydnar: handle custom surface/content flags */
		if ( surfaceFlags != NULL && bspShaders[ i ].surfaceFlags != *surfaceFlags ) {
			continue;
		}
		if ( contentFlags != NULL && bspShaders[ i ].contentFlags != *contentFlags ) {
			continue;
		}

		/* compare name */
		if ( !Q_stricmp( shader, bspShaders[ i ].shader ) ) {
			return i;
		}
	}

	/* get shaderinfo */
	si = ShaderInfoForShader( shader );

	/* emit a new shader */
	if ( i == MAX_MAP_SHADERS ) {
		Error( "MAX_MAP_SHADERS" );
	}
	numBSPShaders++;
	strcpy( bspShaders[ i ].shader, shader );
	bspShaders[ i ].surfaceFlags = si->surfaceFlags;
	bspShaders[ i ].contentFlags = si->contentFlags;

	/* handle custom content/surface flags */
	if ( surfaceFlags != NULL ) {
		bspShaders[ i ].surfaceFlags = *surfaceFlags;
	}
	if ( contentFlags != NULL ) {
		bspShaders[ i ].contentFlags = *contentFlags;
	}

	/* recursively emit any damage shaders */
	if ( si->damageShader != NULL && si->damageShader[ 0 ] != '\0' ) {
		Sys_FPrintf( SYS_VRB, "Shader %s has damage shader %s\n", si->shader, si->damageShader );
		EmitShader( si->damageShader, NULL, NULL );
	}

	/* return it */
	return i;
}