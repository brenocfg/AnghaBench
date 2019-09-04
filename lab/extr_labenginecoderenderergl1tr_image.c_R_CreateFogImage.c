#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int byte ;
struct TYPE_4__ {int* (* Hunk_AllocateTempMemory ) (int) ;int /*<<< orphan*/  (* Hunk_FreeTempMemory ) (int*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  fogImage; } ;

/* Variables and functions */
 int FOG_S ; 
 int FOG_T ; 
 int /*<<< orphan*/  IMGFLAG_CLAMPTOEDGE ; 
 int /*<<< orphan*/  IMGTYPE_COLORALPHA ; 
 int /*<<< orphan*/  R_CreateImage (char*,int*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float R_FogFactor (int,int) ; 
 TYPE_2__ ri ; 
 int* stub1 (int) ; 
 int /*<<< orphan*/  stub2 (int*) ; 
 TYPE_1__ tr ; 

__attribute__((used)) static void R_CreateFogImage( void ) {
	int		x,y;
	byte	*data;
	float	d;

	data = ri.Hunk_AllocateTempMemory( FOG_S * FOG_T * 4 );

	// S is distance, T is depth
	for (x=0 ; x<FOG_S ; x++) {
		for (y=0 ; y<FOG_T ; y++) {
			d = R_FogFactor( ( x + 0.5f ) / FOG_S, ( y + 0.5f ) / FOG_T );

			data[(y*FOG_S+x)*4+0] = 
			data[(y*FOG_S+x)*4+1] = 
			data[(y*FOG_S+x)*4+2] = 255;
			data[(y*FOG_S+x)*4+3] = 255*d;
		}
	}
	tr.fogImage = R_CreateImage("*fog", (byte *)data, FOG_S, FOG_T, IMGTYPE_COLORALPHA, IMGFLAG_CLAMPTOEDGE, 0 );
	ri.Hunk_FreeTempMemory( data );
}