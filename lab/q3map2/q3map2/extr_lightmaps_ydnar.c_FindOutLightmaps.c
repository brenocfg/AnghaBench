#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__* vec3_t ;
struct TYPE_17__ {scalar_t__ si; } ;
typedef  TYPE_1__ surfaceInfo_t ;
struct TYPE_18__ {int* outLightmapNums; scalar_t__* styles; scalar_t__ used; int customWidth; int customHeight; int* lightmapX; int* lightmapY; int w; int h; int numLightSurfaces; int firstLightSurface; float** solidColor; int /*<<< orphan*/  brightness; scalar_t__* solid; int /*<<< orphan*/ ** twins; } ;
typedef  TYPE_2__ rawLightmap_t ;
typedef  scalar_t__ qboolean ;
struct TYPE_19__ {scalar_t__ freeLuxels; int customWidth; int customHeight; int numShaders; scalar_t__* shaders; int* lightBits; int* bspLightBytes; int* bspDirBytes; int /*<<< orphan*/  numLightmaps; scalar_t__ extLightmapNum; } ;
typedef  TYPE_3__ outLightmap_t ;
typedef  int byte ;
struct TYPE_20__ {scalar_t__ load; } ;

/* Variables and functions */
 scalar_t__ ApproximateLightmap (TYPE_2__*) ; 
 float* BSP_DELUXEL (int,int) ; 
 float* BSP_LUXEL (int,int,int) ; 
 int /*<<< orphan*/  ColorToBytes (scalar_t__*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Error (char*) ; 
 scalar_t__ LS_NONE ; 
 scalar_t__ LoadRBSPFile ; 
 int MAX_LIGHTMAPS ; 
 int MAX_LIGHTMAP_SHADERS ; 
 int /*<<< orphan*/  SetupOutLightmap (TYPE_2__*,TYPE_3__*) ; 
 scalar_t__ TestOutLightmapStamp (TYPE_2__*,int,TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  VectorCopy (float*,scalar_t__*) ; 
 scalar_t__ VectorNormalize (float*,scalar_t__*) ; 
 int /*<<< orphan*/  VectorSet (scalar_t__*,float,float,float) ; 
 scalar_t__ debug ; 
 scalar_t__ deluxemap ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 TYPE_9__* game ; 
 size_t* lightSurfaces ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,TYPE_3__*,int) ; 
 scalar_t__* minLight ; 
 int /*<<< orphan*/  numLightmapShaders ; 
 int numOutLightmaps ; 
 TYPE_3__* outLightmaps ; 
 scalar_t__ qfalse ; 
 TYPE_3__* safe_malloc (int) ; 
 TYPE_1__* surfaceInfos ; 

__attribute__((used)) static void FindOutLightmaps( rawLightmap_t *lm ){
	int i, j, lightmapNum, xMax, yMax, x, y, sx, sy, ox, oy, offset, temp;
	outLightmap_t       *olm;
	surfaceInfo_t       *info;
	float               *luxel, *deluxel;
	vec3_t color, direction;
	byte                *pixel;
	qboolean ok;


	/* set default lightmap number (-3 = LIGHTMAP_BY_VERTEX) */
	for ( lightmapNum = 0; lightmapNum < MAX_LIGHTMAPS; lightmapNum++ )
		lm->outLightmapNums[ lightmapNum ] = -3;

	/* can this lightmap be approximated with vertex color? */
	if ( ApproximateLightmap( lm ) ) {
		return;
	}

	/* walk list */
	for ( lightmapNum = 0; lightmapNum < MAX_LIGHTMAPS; lightmapNum++ )
	{
		/* early out */
		if ( lm->styles[ lightmapNum ] == LS_NONE ) {
			continue;
		}

		/* don't store twinned lightmaps */
		if ( lm->twins[ lightmapNum ] != NULL ) {
			continue;
		}

		/* if this is a styled lightmap, try some normalized locations first */
		ok = qfalse;
		if ( lightmapNum > 0 && outLightmaps != NULL ) {
			/* loop twice */
			for ( j = 0; j < 2; j++ )
			{
				/* try identical position */
				for ( i = 0; i < numOutLightmaps; i++ )
				{
					/* get the output lightmap */
					olm = &outLightmaps[ i ];

					/* simple early out test */
					if ( olm->freeLuxels < lm->used ) {
						continue;
					}

					/* don't store non-custom raw lightmaps on custom bsp lightmaps */
					if ( olm->customWidth != lm->customWidth ||
						 olm->customHeight != lm->customHeight ) {
						continue;
					}

					/* try identical */
					if ( j == 0 ) {
						x = lm->lightmapX[ 0 ];
						y = lm->lightmapY[ 0 ];
						ok = TestOutLightmapStamp( lm, lightmapNum, olm, x, y );
					}

					/* try shifting */
					else
					{
						for ( sy = -1; sy <= 1; sy++ )
						{
							for ( sx = -1; sx <= 1; sx++ )
							{
								x = lm->lightmapX[ 0 ] + sx * ( olm->customWidth >> 1 );  //%	lm->w;
								y = lm->lightmapY[ 0 ] + sy * ( olm->customHeight >> 1 ); //%	lm->h;
								ok = TestOutLightmapStamp( lm, lightmapNum, olm, x, y );

								if ( ok ) {
									break;
								}
							}

							if ( ok ) {
								break;
							}
						}
					}

					if ( ok ) {
						break;
					}
				}

				if ( ok ) {
					break;
				}
			}
		}

		/* try normal placement algorithm */
		if ( ok == qfalse ) {
			/* reset origin */
			x = 0;
			y = 0;

			/* walk the list of lightmap pages */
			for ( i = 0; i < numOutLightmaps; i++ )
			{
				/* get the output lightmap */
				olm = &outLightmaps[ i ];

				/* simple early out test */
				if ( olm->freeLuxels < lm->used ) {
					continue;
				}

				/* don't store non-custom raw lightmaps on custom bsp lightmaps */
				if ( olm->customWidth != lm->customWidth ||
					 olm->customHeight != lm->customHeight ) {
					continue;
				}

				/* set maxs */
				if ( lm->solid[ lightmapNum ] ) {
					xMax = olm->customWidth;
					yMax = olm->customHeight;
				}
				else
				{
					xMax = ( olm->customWidth - lm->w ) + 1;
					yMax = ( olm->customHeight - lm->h ) + 1;
				}

				/* walk the origin around the lightmap */
				for ( y = 0; y < yMax; y++ )
				{
					for ( x = 0; x < xMax; x++ )
					{
						/* find a fine tract of lauhnd */
						ok = TestOutLightmapStamp( lm, lightmapNum, olm, x, y );

						if ( ok ) {
							break;
						}
					}

					if ( ok ) {
						break;
					}
				}

				if ( ok ) {
					break;
				}

				/* reset x and y */
				x = 0;
				y = 0;
			}
		}

		/* no match? */
		if ( ok == qfalse ) {
			/* allocate two new output lightmaps */
			numOutLightmaps += 2;
			olm = safe_malloc( numOutLightmaps * sizeof( outLightmap_t ) );
			if ( !olm )
			{
				Error( "FindOutLightmaps: Failed to allocate memory.\n" );
			}

			if ( outLightmaps != NULL && numOutLightmaps > 2 ) {
				memcpy( olm, outLightmaps, ( numOutLightmaps - 2 ) * sizeof( outLightmap_t ) );
				free( outLightmaps );
			}
			outLightmaps = olm;

			/* initialize both out lightmaps */
			SetupOutLightmap( lm, &outLightmaps[ numOutLightmaps - 2 ] );
			SetupOutLightmap( lm, &outLightmaps[ numOutLightmaps - 1 ] );

			/* set out lightmap */
			i = numOutLightmaps - 2;
			olm = &outLightmaps[ i ];

			/* set stamp xy origin to the first surface lightmap */
			if ( lightmapNum > 0 ) {
				x = lm->lightmapX[ 0 ];
				y = lm->lightmapY[ 0 ];
			}
		}

		/* if this is a style-using lightmap, it must be exported */
		if ( lightmapNum > 0 && game->load != LoadRBSPFile ) {
			olm->extLightmapNum = 0;
		}

		/* add the surface lightmap to the bsp lightmap */
		lm->outLightmapNums[ lightmapNum ] = i;
		lm->lightmapX[ lightmapNum ] = x;
		lm->lightmapY[ lightmapNum ] = y;
		olm->numLightmaps++;

		/* add shaders */
		for ( i = 0; i < lm->numLightSurfaces; i++ )
		{
			/* get surface info */
			info = &surfaceInfos[ lightSurfaces[ lm->firstLightSurface + i ] ];

			/* test for shader */
			for ( j = 0; j < olm->numShaders; j++ )
			{
				if ( olm->shaders[ j ] == info->si ) {
					break;
				}
			}

			/* if it doesn't exist, add it */
			if ( j >= olm->numShaders && olm->numShaders < MAX_LIGHTMAP_SHADERS ) {
				olm->shaders[ olm->numShaders ] = info->si;
				olm->numShaders++;
				numLightmapShaders++;
			}
		}

		/* set maxs */
		if ( lm->solid[ lightmapNum ] ) {
			xMax = 1;
			yMax = 1;
		}
		else
		{
			xMax = lm->w;
			yMax = lm->h;
		}

		/* mark the bits used */
		for ( y = 0; y < yMax; y++ )
		{
			for ( x = 0; x < xMax; x++ )
			{
				/* get luxel */
				luxel = BSP_LUXEL( lightmapNum, x, y );
				deluxel = BSP_DELUXEL( x, y );
				if ( luxel[ 0 ] < 0.0f && !lm->solid[ lightmapNum ] ) {
					continue;
				}

				/* set minimum light */
				if ( lm->solid[ lightmapNum ] ) {
					if ( debug ) {
						VectorSet( color, 255.0f, 0.0f, 0.0f );
					}
					else{
						VectorCopy( lm->solidColor[ lightmapNum ], color );
					}
				}
				else{
					VectorCopy( luxel, color );
				}

				/* styles are not affected by minlight */
				if ( lightmapNum == 0 ) {
					for ( i = 0; i < 3; i++ )
					{
						if ( color[ i ] < minLight[ i ] ) {
							color[ i ] = minLight[ i ];
						}
					}
				}

				/* get bsp lightmap coords  */
				ox = x + lm->lightmapX[ lightmapNum ];
				oy = y + lm->lightmapY[ lightmapNum ];
				offset = ( oy * olm->customWidth ) + ox;

				/* flag pixel as used */
				olm->lightBits[ offset >> 3 ] |= ( 1 << ( offset & 7 ) );
				olm->freeLuxels--;

				/* store color */
				pixel = olm->bspLightBytes + ( ( ( oy * olm->customWidth ) + ox ) * 3 );
				ColorToBytes( color, pixel, lm->brightness );

				/* store direction */
				if ( deluxemap ) {
					/* normalize average light direction */
					if ( VectorNormalize( deluxel, direction ) ) {
						/* encode [-1,1] in [0,255] */
						pixel = olm->bspDirBytes + ( ( ( oy * olm->customWidth ) + ox ) * 3 );
						for ( i = 0; i < 3; i++ )
						{
							temp = ( direction[ i ] + 1.0f ) * 127.5f;
							if ( temp < 0 ) {
								pixel[ i ] = 0;
							}
							else if ( temp > 255 ) {
								pixel[ i ] = 255;
							}
							else{
								pixel[ i ] = temp;
							}
						}
					}
				}
			}
		}
	}
}