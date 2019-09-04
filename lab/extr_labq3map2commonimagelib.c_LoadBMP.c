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
typedef  scalar_t__ qboolean ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*,char const*) ; 
 int bufLittleLong (int /*<<< orphan*/ *,int,int*) ; 
 int bufLittleShort (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ qfalse ; 
 scalar_t__ qtrue ; 
 int /*<<< orphan*/ * safe_malloc (int) ; 
 int vfsLoadFile (char const*,void**,int /*<<< orphan*/ ) ; 

void LoadBMP( const char *filename, byte **pic, byte **palette, int *width, int *height ){
	byte  *out;
	int i;
	int bfSize;
	int bfOffBits;
	int structSize;
	int bcWidth;
	int bcHeight;
	int bcPlanes;
	int bcBitCount;
	byte bcPalette[1024];
	qboolean flipped;
	byte *in;
	int len, pos = 0;

	len = vfsLoadFile( filename, (void **)&in, 0 );
	if ( len == -1 ) {
		Error( "Couldn't read %s", filename );
	}

	i = bufLittleShort( in, len, &pos );
	if ( i != 'B' + ( 'M' << 8 ) ) {
		Error( "%s is not a bmp file", filename );
	}

	bfSize = bufLittleLong( in, len, &pos );
	bufLittleShort( in, len, &pos );
	bufLittleShort( in, len, &pos );
	bfOffBits = bufLittleLong( in, len, &pos );

	// the size will tell us if it is a
	// bitmapinfo or a bitmapcore
	structSize = bufLittleLong( in, len, &pos );
	if ( structSize == 40 ) {
		// bitmapinfo
		bcWidth = bufLittleLong( in, len, &pos );
		bcHeight = bufLittleLong( in, len, &pos );
		bcPlanes = bufLittleShort( in, len, &pos );
		bcBitCount = bufLittleShort( in, len, &pos );

		pos += 24;

		if ( palette ) {
			memcpy( bcPalette, in + pos, 1024 );
			pos += 1024;
			*palette = safe_malloc( 768 );

			for ( i = 0 ; i < 256 ; i++ )
			{
				( *palette )[i * 3 + 0] = bcPalette[i * 4 + 2];
				( *palette )[i * 3 + 1] = bcPalette[i * 4 + 1];
				( *palette )[i * 3 + 2] = bcPalette[i * 4 + 0];
			}
		}
	}
	else if ( structSize == 12 ) {
		// bitmapcore
		bcWidth = bufLittleShort( in, len, &pos );
		bcHeight = bufLittleShort( in, len, &pos );
		bcPlanes = bufLittleShort( in, len, &pos );
		bcBitCount = bufLittleShort( in, len, &pos );

		if ( palette ) {
			memcpy( bcPalette, in + pos, 768 );
			pos += 768;
			*palette = safe_malloc( 768 );

			for ( i = 0 ; i < 256 ; i++ ) {
				( *palette )[i * 3 + 0] = bcPalette[i * 3 + 2];
				( *palette )[i * 3 + 1] = bcPalette[i * 3 + 1];
				( *palette )[i * 3 + 2] = bcPalette[i * 3 + 0];
			}
		}
	}
	else {
		Error( "%s had strange struct size", filename );
		return;
	}

	if ( bcPlanes != 1 ) {
		Error( "%s was not a single plane image", filename );
	}

	if ( bcBitCount != 8 ) {
		Error( "%s was not an 8 bit image", filename );
	}

	if ( bcHeight < 0 ) {
		bcHeight = -bcHeight;
		flipped = qtrue;
	}
	else {
		flipped = qfalse;
	}

	if ( width ) {
		*width = bcWidth;
	}
	if ( height ) {
		*height = bcHeight;
	}

	if ( !pic ) {
		free( in );
		return;
	}

	out = safe_malloc( bcWidth * bcHeight );
	*pic = out;
	pos = bfOffBits;

	if ( flipped ) {
		for ( i = 0 ; i < bcHeight ; i++ ) {
			memcpy( out + bcWidth * ( bcHeight - 1 - i ), in + pos, bcWidth );
			pos += bcWidth;
		}
	}
	else {
		memcpy( out, in + pos, bcWidth * bcHeight );
		pos += bcWidth * bcHeight;
	}

	free( in );
}