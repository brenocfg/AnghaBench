#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ qboolean ;
typedef  int /*<<< orphan*/  brush_t ;
struct TYPE_4__ {int* portalareas; int compileFlags; int /*<<< orphan*/  brushNum; scalar_t__ entityNum; } ;

/* Variables and functions */
 int C_DETAIL ; 
 int C_HINT ; 
 int C_LIQUID ; 
 int /*<<< orphan*/ * FinishBrush () ; 
 int /*<<< orphan*/  ParseRawBrush (scalar_t__) ; 
 int /*<<< orphan*/  RemoveDuplicateBrushPlanes (TYPE_1__*) ; 
 int /*<<< orphan*/  SetBrushContents (TYPE_1__*) ; 
 TYPE_1__* buildBrush ; 
 int /*<<< orphan*/  entitySourceBrushes ; 
 scalar_t__ noHint ; 
 scalar_t__ nodetail ; 
 scalar_t__ nowater ; 
 scalar_t__ numMapEntities ; 

__attribute__((used)) static void ParseBrush( qboolean onlyLights ){
	brush_t *b;


	/* parse the brush out of the map */
	ParseRawBrush( onlyLights );

	/* only go this far? */
	if ( onlyLights ) {
		return;
	}

	/* set some defaults */
	buildBrush->portalareas[ 0 ] = -1;
	buildBrush->portalareas[ 1 ] = -1;
	buildBrush->entityNum = numMapEntities - 1;
	buildBrush->brushNum = entitySourceBrushes;

	/* if there are mirrored planes, the entire brush is invalid */
	if ( !RemoveDuplicateBrushPlanes( buildBrush ) ) {
		return;
	}

	/* get the content for the entire brush */
	SetBrushContents( buildBrush );

	/* allow detail brushes to be removed */
	if ( nodetail && ( buildBrush->compileFlags & C_DETAIL ) ) {
		//%	FreeBrush( buildBrush );
		return;
	}

	/* allow liquid brushes to be removed */
	if ( nowater && ( buildBrush->compileFlags & C_LIQUID ) ) {
		//%	FreeBrush( buildBrush );
		return;
	}

	/* ydnar: allow hint brushes to be removed */
	if ( noHint && ( buildBrush->compileFlags & C_HINT ) ) {
		//%	FreeBrush( buildBrush );
		return;
	}

	/* finish the brush */
	b = FinishBrush();
}