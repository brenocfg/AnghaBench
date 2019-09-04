#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int byte ;
struct TYPE_3__ {int id_length; int colormap_type; int image_type; int colormap_index; int colormap_length; int colormap_size; int x_origin; int y_origin; int width; int height; int pixel_size; int attributes; } ;
typedef  TYPE_1__ TargaHeader ;

/* Variables and functions */
 int /*<<< orphan*/  Sys_Printf (char*,int,int) ; 
 int /*<<< orphan*/  TargaError (TYPE_1__*,char*) ; 
 int* safe_malloc (int) ; 

void LoadTGABuffer( const byte *f, const byte *enddata, byte **pic, int *width, int *height ){
	int x, y, row_inc, compressed, readpixelcount, red, green, blue, alpha, runlen, pindex, alphabits, image_width, image_height;
	byte *pixbuf, *image_rgba;
	const byte *fin;
	unsigned char *p;
	TargaHeader targa_header;
	unsigned char palette[256 * 4];

	*pic = NULL;

	// abort if it is too small to parse
	if ( enddata - f < 19 ) {
		return;
	}

	targa_header.id_length = f[0];
	targa_header.colormap_type = f[1];
	targa_header.image_type = f[2];

	targa_header.colormap_index = f[3] + f[4] * 256;
	targa_header.colormap_length = f[5] + f[6] * 256;
	targa_header.colormap_size = f[7];
	targa_header.x_origin = f[8] + f[9] * 256;
	targa_header.y_origin = f[10] + f[11] * 256;
	targa_header.width = image_width = f[12] + f[13] * 256;
	targa_header.height = image_height = f[14] + f[15] * 256;

	targa_header.pixel_size = f[16];
	targa_header.attributes = f[17];

	// advance to end of header
	fin = f + 18;

	// skip TARGA image comment (usually 0 bytes)
	fin += targa_header.id_length;

	// read/skip the colormap if present (note: according to the TARGA spec it
	// can be present even on truecolor or greyscale images, just not used by
	// the image data)
	if ( targa_header.colormap_type ) {
		if ( targa_header.colormap_length > 256 ) {
			TargaError( &targa_header, "LoadTGA: only up to 256 colormap_length supported\n" );
			return;
		}
		if ( targa_header.colormap_index ) {
			TargaError( &targa_header, "LoadTGA: colormap_index not supported\n" );
			return;
		}
		if ( targa_header.colormap_size == 24 ) {
			for ( x = 0; x < targa_header.colormap_length; x++ )
			{
				palette[x * 4 + 2] = *fin++;
				palette[x * 4 + 1] = *fin++;
				palette[x * 4 + 0] = *fin++;
				palette[x * 4 + 3] = 255;
			}
		}
		else if ( targa_header.colormap_size == 32 ) {
			for ( x = 0; x < targa_header.colormap_length; x++ )
			{
				palette[x * 4 + 2] = *fin++;
				palette[x * 4 + 1] = *fin++;
				palette[x * 4 + 0] = *fin++;
				palette[x * 4 + 3] = *fin++;
			}
		}
		else
		{
			TargaError( &targa_header, "LoadTGA: Only 32 and 24 bit colormap_size supported\n" );
			return;
		}
	}

	// check our pixel_size restrictions according to image_type
	if ( targa_header.image_type == 2 || targa_header.image_type == 10 ) {
		if ( targa_header.pixel_size != 24 && targa_header.pixel_size != 32 ) {
			TargaError( &targa_header, "LoadTGA: only 24bit and 32bit pixel sizes supported for type 2 and type 10 images\n" );
			return;
		}
	}
	else if ( targa_header.image_type == 1 || targa_header.image_type == 9 ) {
		if ( targa_header.pixel_size != 8 ) {
			TargaError( &targa_header, "LoadTGA: only 8bit pixel size for type 1, 3, 9, and 11 images supported\n" );
			return;
		}
	}
	else if ( targa_header.image_type == 3 || targa_header.image_type == 11 ) {
		if ( targa_header.pixel_size != 8 ) {
			TargaError( &targa_header, "LoadTGA: only 8bit pixel size for type 1, 3, 9, and 11 images supported\n" );
			return;
		}
	}
	else
	{
		TargaError( &targa_header, "LoadTGA: Only type 1, 2, 3, 9, 10, and 11 targa RGB images supported" );
		return;
	}

	if ( targa_header.attributes & 0x10 ) {
		TargaError( &targa_header, "LoadTGA: origin must be in top left or bottom left, top right and bottom right are not supported\n" );
		return;
	}

	// number of attribute bits per pixel, we only support 0 or 8
	alphabits = targa_header.attributes & 0x0F;
	if ( alphabits != 8 && alphabits != 0 ) {
		TargaError( &targa_header, "LoadTGA: only 0 or 8 attribute (alpha) bits supported\n" );
		return;
	}

	image_rgba = safe_malloc( image_width * image_height * 4 );
	if ( !image_rgba ) {
		Sys_Printf( "LoadTGA: not enough memory for %i by %i image\n", image_width, image_height );
		return;
	}

	// If bit 5 of attributes isn't set, the image has been stored from bottom to top
	if ( ( targa_header.attributes & 0x20 ) == 0 ) {
		pixbuf = image_rgba + ( image_height - 1 ) * image_width * 4;
		row_inc = -image_width * 4 * 2;
	}
	else
	{
		pixbuf = image_rgba;
		row_inc = 0;
	}

	compressed = targa_header.image_type == 9 || targa_header.image_type == 10 || targa_header.image_type == 11;
	x = 0;
	y = 0;
	red = green = blue = alpha = 255;
	while ( y < image_height )
	{
		// decoder is mostly the same whether it's compressed or not
		readpixelcount = 1000000;
		runlen = 1000000;
		if ( compressed && fin < enddata ) {
			runlen = *fin++;
			// high bit indicates this is an RLE compressed run
			if ( runlen & 0x80 ) {
				readpixelcount = 1;
			}
			runlen = 1 + ( runlen & 0x7f );
		}

		while ( ( runlen-- ) && y < image_height )
		{
			if ( readpixelcount > 0 ) {
				readpixelcount--;
				red = green = blue = alpha = 255;
				if ( fin < enddata ) {
					switch ( targa_header.image_type )
					{
					case 1:
					case 9:
						// colormapped
						pindex = *fin++;
						if ( pindex >= targa_header.colormap_length ) {
							pindex = 0; // error
						}
						p = palette + pindex * 4;
						red = p[0];
						green = p[1];
						blue = p[2];
						alpha = p[3];
						break;
					case 2:
					case 10:
						// BGR or BGRA
						blue = *fin++;
						if ( fin < enddata ) {
							green = *fin++;
						}
						if ( fin < enddata ) {
							red = *fin++;
						}
						if ( targa_header.pixel_size == 32 && fin < enddata ) {
							alpha = *fin++;
						}
						break;
					case 3:
					case 11:
						// greyscale
						red = green = blue = *fin++;
						break;
					}
					if ( !alphabits ) {
						alpha = 255;
					}
				}
			}
			*pixbuf++ = red;
			*pixbuf++ = green;
			*pixbuf++ = blue;
			*pixbuf++ = alpha;
			x++;
			if ( x == image_width ) {
				// end of line, advance to next
				x = 0;
				y++;
				pixbuf += row_inc;
			}
		}
	}

	*pic = image_rgba;
	if ( width ) {
		*width = image_width;
	}
	if ( height ) {
		*height = image_height;
	}
}