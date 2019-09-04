#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int manufacturer; int version; int encoding; int bits_per_pixel; int color_planes; int data; void* palette_type; void* bytes_per_line; void* vres; void* hres; void* ymax; void* xmax; scalar_t__ ymin; scalar_t__ xmin; } ;
typedef  TYPE_1__ pcx_t ;
typedef  int byte ;

/* Variables and functions */
 void* LittleShort (int) ; 
 int /*<<< orphan*/  SaveFile (char const*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* safe_malloc (int) ; 

void WritePCXfile( const char *filename, byte *data,
				   int width, int height, byte *palette ){
	int i, j, length;
	pcx_t   *pcx;
	byte        *pack;

	pcx = safe_malloc( width * height * 2 + 1000 );
	memset( pcx, 0, sizeof( *pcx ) );

	pcx->manufacturer = 0x0a;   // PCX id
	pcx->version = 5;           // 256 color
	pcx->encoding = 1;      // uncompressed
	pcx->bits_per_pixel = 8;        // 256 color
	pcx->xmin = 0;
	pcx->ymin = 0;
	pcx->xmax = LittleShort( (short)( width - 1 ) );
	pcx->ymax = LittleShort( (short)( height - 1 ) );
	pcx->hres = LittleShort( (short)width );
	pcx->vres = LittleShort( (short)height );
	pcx->color_planes = 1;      // chunky image
	pcx->bytes_per_line = LittleShort( (short)width );
	pcx->palette_type = LittleShort( 1 );     // not a grey scale

	// pack the image
	pack = &pcx->data;

	for ( i = 0 ; i < height ; i++ )
	{
		for ( j = 0 ; j < width ; j++ )
		{
			if ( ( *data & 0xc0 ) != 0xc0 ) {
				*pack++ = *data++;
			}
			else
			{
				*pack++ = 0xc1;
				*pack++ = *data++;
			}
		}
	}

	// write the palette
	*pack++ = 0x0c; // palette ID byte
	for ( i = 0 ; i < 768 ; i++ )
		*pack++ = *palette++;

// write output file
	length = pack - (byte *)pcx;
	SaveFile( filename, pcx, length );

	free( pcx );
}