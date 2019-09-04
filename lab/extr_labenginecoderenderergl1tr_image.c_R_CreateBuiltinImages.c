#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  data ;
typedef  int byte ;
struct TYPE_2__ {int identityLightByte; void** scratchImage; void* identityLightImage; void* whiteImage; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Memset (int***,int,int) ; 
 int DEFAULT_SIZE ; 
 int IMGFLAG_CLAMPTOEDGE ; 
 int IMGFLAG_NONE ; 
 int IMGFLAG_PICMIP ; 
 int /*<<< orphan*/  IMGTYPE_COLORALPHA ; 
 int /*<<< orphan*/  R_CreateDefaultImage () ; 
 int /*<<< orphan*/  R_CreateDlightImage () ; 
 int /*<<< orphan*/  R_CreateFogImage () ; 
 void* R_CreateImage (char*,int*,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_1__ tr ; 

void R_CreateBuiltinImages( void ) {
	int		x,y;
	byte	data[DEFAULT_SIZE][DEFAULT_SIZE][4];

	R_CreateDefaultImage();

	// we use a solid white image instead of disabling texturing
	Com_Memset( data, 255, sizeof( data ) );
	tr.whiteImage = R_CreateImage("*white", (byte *)data, 8, 8, IMGTYPE_COLORALPHA, IMGFLAG_NONE, 0);

	// with overbright bits active, we need an image which is some fraction of full color,
	// for default lightmaps, etc
	for (x=0 ; x<DEFAULT_SIZE ; x++) {
		for (y=0 ; y<DEFAULT_SIZE ; y++) {
			data[y][x][0] = 
			data[y][x][1] = 
			data[y][x][2] = tr.identityLightByte;
			data[y][x][3] = 255;			
		}
	}

	tr.identityLightImage = R_CreateImage("*identityLight", (byte *)data, 8, 8, IMGTYPE_COLORALPHA, IMGFLAG_NONE, 0);


	for(x=0;x<32;x++) {
		// scratchimage is usually used for cinematic drawing
		tr.scratchImage[x] = R_CreateImage("*scratch", (byte *)data, DEFAULT_SIZE, DEFAULT_SIZE, IMGTYPE_COLORALPHA, IMGFLAG_PICMIP | IMGFLAG_CLAMPTOEDGE, 0);
	}

	R_CreateDlightImage();
	R_CreateFogImage();
}