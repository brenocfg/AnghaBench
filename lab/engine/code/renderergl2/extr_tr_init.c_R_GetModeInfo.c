#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int width; int height; float pixelAspect; } ;
typedef  TYPE_1__ vidmode_t ;
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_13__ {int integer; } ;
struct TYPE_12__ {int integer; } ;
struct TYPE_11__ {float value; } ;
struct TYPE_10__ {int integer; } ;
struct TYPE_9__ {int integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_7__* r_buffheight ; 
 TYPE_6__* r_buffwidth ; 
 TYPE_5__* r_customPixelAspect ; 
 TYPE_4__* r_customheight ; 
 TYPE_3__* r_customwidth ; 
 TYPE_1__* r_vidModes ; 
 int s_numVidModes ; 

qboolean R_GetModeInfo( int *width, int *height, int *buff_width, int *buff_height, float *windowAspect, int mode ) {
	vidmode_t	*vm;
	float			pixelAspect;

	if ( mode < -1 ) {
		return qfalse;
	}
	if ( mode >= s_numVidModes ) {
		return qfalse;
	}

	if ( mode == -1 ) {
		*width = r_customwidth->integer;
		*height = r_customheight->integer;
		*buff_width = r_buffwidth->integer;
		*buff_height = r_buffheight->integer;
		pixelAspect = r_customPixelAspect->value;
	} else {
		vm = &r_vidModes[mode];

		*width  = vm->width;
		*height = vm->height;
		*buff_width = r_buffwidth->integer;
		*buff_height = r_buffheight->integer;
		pixelAspect = vm->pixelAspect;
	}

	*windowAspect = (float)*width / ( *height * pixelAspect );

	return qtrue;
}