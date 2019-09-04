#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int filelen; int fileofs; } ;
typedef  TYPE_1__ lump_t ;
typedef  int /*<<< orphan*/  image_t ;
typedef  float byte ;
struct TYPE_13__ {scalar_t__ hardwareType; } ;
struct TYPE_12__ {int integer; } ;
struct TYPE_11__ {scalar_t__ integer; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* Printf ) (int /*<<< orphan*/ ,char*,int) ;int /*<<< orphan*/ * (* Hunk_Alloc ) (int,int /*<<< orphan*/ ) ;} ;
struct TYPE_9__ {int numLightmaps; int /*<<< orphan*/ * lightmaps; } ;

/* Variables and functions */
 scalar_t__ GLHW_PERMEDIA2 ; 
 int /*<<< orphan*/  HSVtoRGB (float,double,double,float*) ; 
 int IMGFLAG_CLAMPTOEDGE ; 
 int IMGFLAG_NOLIGHTSCALE ; 
 int IMGFLAG_NO_COMPRESSION ; 
 int /*<<< orphan*/  IMGTYPE_COLORALPHA ; 
 int LIGHTMAP_SIZE ; 
 int /*<<< orphan*/  PRINT_ALL ; 
 int /*<<< orphan*/  R_ColorShiftLightingBytes (float*,float*) ; 
 int /*<<< orphan*/  R_CreateImage (int /*<<< orphan*/ ,float*,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R_IssuePendingRenderCommands () ; 
 float* fileBase ; 
 TYPE_6__ glConfig ; 
 int /*<<< orphan*/  h_low ; 
 TYPE_5__* r_lightmap ; 
 TYPE_4__* r_vertexLight ; 
 TYPE_3__ ri ; 
 int /*<<< orphan*/ * stub1 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_2__ tr ; 
 int /*<<< orphan*/  va (char*,int) ; 

__attribute__((used)) static	void R_LoadLightmaps( lump_t *l ) {
	byte		*buf, *buf_p;
	int			len;
	byte		image[LIGHTMAP_SIZE*LIGHTMAP_SIZE*4];
	int			i, j;
	float maxIntensity = 0;
	double sumIntensity = 0;

	len = l->filelen;
	if ( !len ) {
		return;
	}
	buf = fileBase + l->fileofs;

	// we are about to upload textures
	R_IssuePendingRenderCommands();

	// create all the lightmaps
	tr.numLightmaps = len / (LIGHTMAP_SIZE * LIGHTMAP_SIZE * 3);
	if ( tr.numLightmaps == 1 ) {
		//FIXME: HACK: maps with only one lightmap turn up fullbright for some reason.
		//this avoids this, but isn't the correct solution.
		tr.numLightmaps++;
	}

	// if we are in r_vertexLight mode, we don't need the lightmaps at all
	if ( r_vertexLight->integer || glConfig.hardwareType == GLHW_PERMEDIA2 ) {
		return;
	}

	tr.lightmaps = ri.Hunk_Alloc( tr.numLightmaps * sizeof(image_t *), h_low );
	for ( i = 0 ; i < tr.numLightmaps ; i++ ) {
		// expand the 24 bit on-disk to 32 bit
		buf_p = buf + i * LIGHTMAP_SIZE*LIGHTMAP_SIZE * 3;

		if ( r_lightmap->integer == 2 )
		{	// color code by intensity as development tool	(FIXME: check range)
			for ( j = 0; j < LIGHTMAP_SIZE * LIGHTMAP_SIZE; j++ )
			{
				float r = buf_p[j*3+0];
				float g = buf_p[j*3+1];
				float b = buf_p[j*3+2];
				float intensity;
				float out[3] = {0.0, 0.0, 0.0};

				intensity = 0.33f * r + 0.685f * g + 0.063f * b;

				if ( intensity > 255 )
					intensity = 1.0f;
				else
					intensity /= 255.0f;

				if ( intensity > maxIntensity )
					maxIntensity = intensity;

				HSVtoRGB( intensity, 1.00, 0.50, out );

				image[j*4+0] = out[0] * 255;
				image[j*4+1] = out[1] * 255;
				image[j*4+2] = out[2] * 255;
				image[j*4+3] = 255;

				sumIntensity += intensity;
			}
		} else {
			for ( j = 0 ; j < LIGHTMAP_SIZE * LIGHTMAP_SIZE; j++ ) {
				R_ColorShiftLightingBytes( &buf_p[j*3], &image[j*4] );
				image[j*4+3] = 255;
			}
		}
		tr.lightmaps[i] = R_CreateImage( va("*lightmap%d",i), image, 
			LIGHTMAP_SIZE, LIGHTMAP_SIZE, IMGTYPE_COLORALPHA,
			IMGFLAG_NOLIGHTSCALE | IMGFLAG_NO_COMPRESSION | IMGFLAG_CLAMPTOEDGE, 0 );
	}

	if ( r_lightmap->integer == 2 )	{
		ri.Printf( PRINT_ALL, "Brightest lightmap value: %d\n", ( int ) ( maxIntensity * 255 ) );
	}
}