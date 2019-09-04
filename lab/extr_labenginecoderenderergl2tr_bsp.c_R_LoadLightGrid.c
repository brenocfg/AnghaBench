#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {float* lightGridInverseSize; float* lightGridSize; int* lightGridOrigin; int* lightGridBounds; int* lightGridData; int* lightGrid16; int /*<<< orphan*/  baseName; TYPE_1__* bmodels; } ;
typedef  TYPE_2__ world_t ;
typedef  float* vec4_t ;
typedef  int* vec3_t ;
struct TYPE_10__ {int filelen; scalar_t__ fileofs; } ;
typedef  TYPE_3__ lump_t ;
typedef  int /*<<< orphan*/  filename ;
struct TYPE_12__ {scalar_t__ integer; } ;
struct TYPE_11__ {int* (* Hunk_Alloc ) (int,int /*<<< orphan*/ ) ;int (* FS_ReadFile ) (char*,void**) ;int /*<<< orphan*/  (* FS_FreeFile ) (float*) ;int /*<<< orphan*/  (* Error ) (int /*<<< orphan*/ ,char*,char*,int,int) ;int /*<<< orphan*/  (* Printf ) (int /*<<< orphan*/ ,char*) ;} ;
struct TYPE_8__ {float** bounds; } ;

/* Variables and functions */
 int /*<<< orphan*/  ColorToRGB16 (float*,int*) ; 
 int /*<<< orphan*/  Com_Memcpy (int*,void*,int) ; 
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_DROP ; 
 int MAX_QPATH ; 
 int /*<<< orphan*/  PRINT_WARNING ; 
 int /*<<< orphan*/  R_ColorShiftLightingBytes (int*,int*) ; 
 int /*<<< orphan*/  R_ColorShiftLightingFloats (float*,float*) ; 
 int ceil (float) ; 
 scalar_t__ fileBase ; 
 int floor (float) ; 
 int /*<<< orphan*/  h_low ; 
 TYPE_6__* r_hdr ; 
 TYPE_5__ ri ; 
 TYPE_2__ s_worldData ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 
 int* stub2 (int,int /*<<< orphan*/ ) ; 
 int stub3 (char*,void**) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,char*,char*,int,int) ; 
 int* stub5 (int,int /*<<< orphan*/ ) ; 
 int* stub6 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (float*) ; 

void R_LoadLightGrid( lump_t *l ) {
	int		i;
	vec3_t	maxs;
	int		numGridPoints;
	world_t	*w;
	float	*wMins, *wMaxs;

	w = &s_worldData;

	w->lightGridInverseSize[0] = 1.0f / w->lightGridSize[0];
	w->lightGridInverseSize[1] = 1.0f / w->lightGridSize[1];
	w->lightGridInverseSize[2] = 1.0f / w->lightGridSize[2];

	wMins = w->bmodels[0].bounds[0];
	wMaxs = w->bmodels[0].bounds[1];

	for ( i = 0 ; i < 3 ; i++ ) {
		w->lightGridOrigin[i] = w->lightGridSize[i] * ceil( wMins[i] / w->lightGridSize[i] );
		maxs[i] = w->lightGridSize[i] * floor( wMaxs[i] / w->lightGridSize[i] );
		w->lightGridBounds[i] = (maxs[i] - w->lightGridOrigin[i])/w->lightGridSize[i] + 1;
	}

	numGridPoints = w->lightGridBounds[0] * w->lightGridBounds[1] * w->lightGridBounds[2];

	if ( l->filelen != numGridPoints * 8 ) {
		ri.Printf( PRINT_WARNING, "WARNING: light grid mismatch\n" );
		w->lightGridData = NULL;
		return;
	}

	w->lightGridData = ri.Hunk_Alloc( l->filelen, h_low );
	Com_Memcpy( w->lightGridData, (void *)(fileBase + l->fileofs), l->filelen );

	// deal with overbright bits
	for ( i = 0 ; i < numGridPoints ; i++ ) {
		R_ColorShiftLightingBytes( &w->lightGridData[i*8], &w->lightGridData[i*8] );
		R_ColorShiftLightingBytes( &w->lightGridData[i*8+3], &w->lightGridData[i*8+3] );
	}

	// load hdr lightgrid
	if (r_hdr->integer)
	{
		char filename[MAX_QPATH];
		float *hdrLightGrid;
		int size;

		Com_sprintf( filename, sizeof( filename ), "maps/%s/lightgrid.raw", s_worldData.baseName);
		//ri.Printf(PRINT_ALL, "looking for %s\n", filename);

		size = ri.FS_ReadFile(filename, (void **)&hdrLightGrid);

		if (hdrLightGrid)
		{
			//ri.Printf(PRINT_ALL, "found!\n");

			if (size != sizeof(float) * 6 * numGridPoints)
				ri.Error(ERR_DROP, "Bad size for %s (%i, expected %i)!", filename, size, (int)(sizeof(float)) * 6 * numGridPoints);

			w->lightGrid16 = ri.Hunk_Alloc(sizeof(w->lightGrid16) * 6 * numGridPoints, h_low);

			for (i = 0; i < numGridPoints ; i++)
			{
				vec4_t c;

				c[0] = hdrLightGrid[i * 6];
				c[1] = hdrLightGrid[i * 6 + 1];
				c[2] = hdrLightGrid[i * 6 + 2];
				c[3] = 1.0f;

				R_ColorShiftLightingFloats(c, c);
				ColorToRGB16(c, &w->lightGrid16[i * 6]);

				c[0] = hdrLightGrid[i * 6 + 3];
				c[1] = hdrLightGrid[i * 6 + 4];
				c[2] = hdrLightGrid[i * 6 + 5];
				c[3] = 1.0f;

				R_ColorShiftLightingFloats(c, c);
				ColorToRGB16(c, &w->lightGrid16[i * 6 + 3]);
			}
		}
		else if (0)
		{
			// promote 8-bit lightgrid to 16-bit
			w->lightGrid16 = ri.Hunk_Alloc(sizeof(w->lightGrid16) * 6 * numGridPoints, h_low);

			for (i = 0; i < numGridPoints; i++)
			{
				w->lightGrid16[i * 6]     = w->lightGridData[i * 8] * 257;
				w->lightGrid16[i * 6 + 1] = w->lightGridData[i * 8 + 1] * 257;
				w->lightGrid16[i * 6 + 2] = w->lightGridData[i * 8 + 2] * 257;
				w->lightGrid16[i * 6 + 3] = w->lightGridData[i * 8 + 3] * 257;
				w->lightGrid16[i * 6 + 4] = w->lightGridData[i * 8 + 4] * 257;
				w->lightGrid16[i * 6 + 5] = w->lightGridData[i * 8 + 5] * 257;
			}
		}

		if (hdrLightGrid)
			ri.FS_FreeFile(hdrLightGrid);
	}
}