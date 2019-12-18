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
typedef  float* vec3_t ;
typedef  int /*<<< orphan*/  qboolean ;

/* Variables and functions */
 int /*<<< orphan*/  VectorClear (float*) ; 
 int /*<<< orphan*/  VectorSet (float*,float,float,float) ; 
 float fabs (float) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

qboolean CalcLightmapAxis( vec3_t normal, vec3_t axis ){
	vec3_t absolute;


	/* test */
	if ( normal[ 0 ] == 0.0f && normal[ 1 ] == 0.0f && normal[ 2 ] == 0.0f ) {
		VectorClear( axis );
		return qfalse;
	}

	/* get absolute normal */
	absolute[ 0 ] = fabs( normal[ 0 ] );
	absolute[ 1 ] = fabs( normal[ 1 ] );
	absolute[ 2 ] = fabs( normal[ 2 ] );

	/* test and set */
	if ( absolute[ 2 ] > absolute[ 0 ] - 0.0001f && absolute[ 2 ] > absolute[ 1 ] - 0.0001f ) {
		if ( normal[ 2 ] > 0.0f ) {
			VectorSet( axis, 0.0f, 0.0f, 1.0f );
		}
		else{
			VectorSet( axis, 0.0f, 0.0f, -1.0f );
		}
	}
	else if ( absolute[ 0 ] > absolute[ 1 ] - 0.0001f && absolute[ 0 ] > absolute[ 2 ] - 0.0001f ) {
		if ( normal[ 0 ] > 0.0f ) {
			VectorSet( axis, 1.0f, 0.0f, 0.0f );
		}
		else{
			VectorSet( axis, -1.0f, 0.0f, 0.0f );
		}
	}
	else
	{
		if ( normal[ 1 ] > 0.0f ) {
			VectorSet( axis, 0.0f, 1.0f, 0.0f );
		}
		else{
			VectorSet( axis, 0.0f, -1.0f, 0.0f );
		}
	}

	/* return ok */
	return qtrue;
}