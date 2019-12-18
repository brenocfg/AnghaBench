#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int contentFlags; int compileFlags; int /*<<< orphan*/ * shaderInfo; } ;
typedef  TYPE_1__ side_t ;
typedef  void* qboolean ;
struct TYPE_6__ {int numsides; int contentFlags; int compileFlags; void* opaque; void* detail; TYPE_1__* sides; int /*<<< orphan*/ * contentShader; } ;
typedef  TYPE_2__ brush_t ;
struct TYPE_7__ {int /*<<< orphan*/  mapEntityNum; } ;

/* Variables and functions */
 int C_AREAPORTAL ; 
 int C_DETAIL ; 
 int C_STRUCTURAL ; 
 int C_TRANSLUCENT ; 
 int /*<<< orphan*/  c_areaportals ; 
 int /*<<< orphan*/  c_detail ; 
 int /*<<< orphan*/  c_structural ; 
 int /*<<< orphan*/  entitySourceBrushes ; 
 scalar_t__ fulldetail ; 
 TYPE_3__* mapEnt ; 
 void* qfalse ; 
 void* qtrue ; 
 int /*<<< orphan*/  xml_Select (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

void SetBrushContents( brush_t *b ){
	int contentFlags, compileFlags;
	side_t      *s;
	int i;
	qboolean mixed;


	/* get initial compile flags from first side */
	s = &b->sides[ 0 ];
	contentFlags = s->contentFlags;
	compileFlags = s->compileFlags;
	b->contentShader = s->shaderInfo;
	mixed = qfalse;

	/* get the content/compile flags for every side in the brush */
	for ( i = 1; i < b->numsides; i++, s++ )
	{
		s = &b->sides[ i ];
		if ( s->shaderInfo == NULL ) {
			continue;
		}
		if ( s->contentFlags != contentFlags || s->compileFlags != compileFlags ) {
			mixed = qtrue;
		}
	}

	/* ydnar: getting rid of this stupid warning */
	//%	if( mixed )
	//%		Sys_FPrintf( SYS_VRB,"Entity %i, Brush %i: mixed face contentFlags\n", b->entitynum, b->brushnum );

	/* check for detail & structural */
	if ( ( compileFlags & C_DETAIL ) && ( compileFlags & C_STRUCTURAL ) ) {
		xml_Select( "Mixed detail and structural (defaulting to structural)", mapEnt->mapEntityNum, entitySourceBrushes, qfalse );
		compileFlags &= ~C_DETAIL;
	}

	/* the fulldetail flag will cause detail brushes to be treated like normal brushes */
	if ( fulldetail ) {
		compileFlags &= ~C_DETAIL;
	}

	/* all translucent brushes that aren't specifically made structural will be detail */
	if ( ( compileFlags & C_TRANSLUCENT ) && !( compileFlags & C_STRUCTURAL ) ) {
		compileFlags |= C_DETAIL;
	}

	/* detail? */
	if ( compileFlags & C_DETAIL ) {
		c_detail++;
		b->detail = qtrue;
	}
	else
	{
		c_structural++;
		b->detail = qfalse;
	}

	/* opaque? */
	if ( compileFlags & C_TRANSLUCENT ) {
		b->opaque = qfalse;
	}
	else{
		b->opaque = qtrue;
	}

	/* areaportal? */
	if ( compileFlags & C_AREAPORTAL ) {
		c_areaportals++;
	}

	/* set brush flags */
	b->contentFlags = contentFlags;
	b->compileFlags = compileFlags;
}