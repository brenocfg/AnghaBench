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
struct TYPE_2__ {int image_type; int width; int height; int pixel_size; int attributes; int /*<<< orphan*/  id_length; int /*<<< orphan*/  colormap_type; void* y_origin; void* x_origin; int /*<<< orphan*/  colormap_size; void* colormap_length; void* colormap_index; } ;
typedef  TYPE_1__ tga_t ;

/* Variables and functions */
 int /*<<< orphan*/  PICO_ERROR ; 
 unsigned char* _pico_alloc (int) ; 
 void* _pico_little_short (short) ; 
 int /*<<< orphan*/  _pico_printf (int /*<<< orphan*/ ,char*) ; 

void _terrain_load_tga_buffer( unsigned char *buffer, unsigned char **pic, int *width, int *height ) {
	int row, column;
	int columns, rows, numPixels;
	unsigned char   *pixbuf;
	unsigned char   *buf_p;
	tga_t targa_header;
	unsigned char   *targa_rgba;


	*pic = NULL;

	if ( buffer == NULL ) {
		return;
	}

	buf_p = buffer;

	targa_header.id_length = *buf_p++;
	targa_header.colormap_type = *buf_p++;
	targa_header.image_type = *buf_p++;

	targa_header.colormap_index = _pico_little_short( *(short*)buf_p );
	buf_p += 2;
	targa_header.colormap_length = _pico_little_short( *(short*) buf_p );
	buf_p += 2;
	targa_header.colormap_size = *buf_p++;
	targa_header.x_origin = _pico_little_short( *(short*) buf_p );
	buf_p += 2;
	targa_header.y_origin = _pico_little_short( *(short*) buf_p );
	buf_p += 2;
	targa_header.width = _pico_little_short( *(short*) buf_p );
	buf_p += 2;
	targa_header.height = _pico_little_short( *(short*) buf_p );
	buf_p += 2;
	targa_header.pixel_size = *buf_p++;
	targa_header.attributes = *buf_p++;

	if ( targa_header.image_type != 2 && targa_header.image_type != 10 && targa_header.image_type != 3 ) {
		_pico_printf( PICO_ERROR, "Only type 2 (RGB), 3 (gray), and 10 (RGB) TGA images supported\n" );
		pic = NULL;
		return;
	}

	if ( targa_header.colormap_type != 0 ) {
		_pico_printf( PICO_ERROR, "Indexed color TGA images not supported\n" );
		return;
	}

	if ( targa_header.pixel_size != 32 && targa_header.pixel_size != 24 && targa_header.image_type != 3 ) {
		_pico_printf( PICO_ERROR, "Only 32 or 24 bit TGA images supported (not indexed color)\n" );
		pic = NULL;
		return;
	}

	columns = targa_header.width;
	rows = targa_header.height;
	numPixels = columns * rows;

	if ( width ) {
		*width = columns;
	}
	if ( height ) {
		*height = rows;
	}

	targa_rgba = _pico_alloc( numPixels * 4 );
	*pic = targa_rgba;

	if ( targa_header.id_length != 0 ) {
		buf_p += targa_header.id_length;  // skip TARGA image comment

	}
	if ( targa_header.image_type == 2 || targa_header.image_type == 3 ) {
		// Uncompressed RGB or gray scale image
		for ( row = rows - 1; row >= 0; row-- )
		{
			pixbuf = targa_rgba + row * columns * 4;
			for ( column = 0; column < columns; column++ )
			{
				unsigned char red,green,blue,alphabyte;
				switch ( targa_header.pixel_size )
				{

				case 8:
					blue = *buf_p++;
					green = blue;
					red = blue;
					*pixbuf++ = red;
					*pixbuf++ = green;
					*pixbuf++ = blue;
					*pixbuf++ = 255;
					break;

				case 24:
					blue = *buf_p++;
					green = *buf_p++;
					red = *buf_p++;
					*pixbuf++ = red;
					*pixbuf++ = green;
					*pixbuf++ = blue;
					*pixbuf++ = 255;
					break;
				case 32:
					blue = *buf_p++;
					green = *buf_p++;
					red = *buf_p++;
					alphabyte = *buf_p++;
					*pixbuf++ = red;
					*pixbuf++ = green;
					*pixbuf++ = blue;
					*pixbuf++ = alphabyte;
					break;
				default:
					break;
				}
			}
		}
	}

	/* rle encoded pixels */
	else if ( targa_header.image_type == 10 ) {
		unsigned char red,green,blue,alphabyte,packetHeader,packetSize,j;

		red = 0;
		green = 0;
		blue = 0;
		alphabyte = 0xff;

		for ( row = rows - 1; row >= 0; row-- ) {
			pixbuf = targa_rgba + row * columns * 4;
			for ( column = 0; column < columns; ) {
				packetHeader = *buf_p++;
				packetSize = 1 + ( packetHeader & 0x7f );
				if ( packetHeader & 0x80 ) {        // run-length packet
					switch ( targa_header.pixel_size ) {
					case 24:
						blue = *buf_p++;
						green = *buf_p++;
						red = *buf_p++;
						alphabyte = 255;
						break;
					case 32:
						blue = *buf_p++;
						green = *buf_p++;
						red = *buf_p++;
						alphabyte = *buf_p++;
						break;
					default:
						//Error("LoadTGA: illegal pixel_size '%d' in file '%s'\n", targa_header.pixel_size, name );
						break;
					}

					for ( j = 0; j < packetSize; j++ ) {
						*pixbuf++ = red;
						*pixbuf++ = green;
						*pixbuf++ = blue;
						*pixbuf++ = alphabyte;
						column++;
						if ( column == columns ) { // run spans across rows
							column = 0;
							if ( row > 0 ) {
								row--;
							}
							else{
								goto breakOut;
							}
							pixbuf = targa_rgba + row * columns * 4;
						}
					}
				}
				else {                            // non run-length packet
					for ( j = 0; j < packetSize; j++ ) {
						switch ( targa_header.pixel_size ) {
						case 24:
							blue = *buf_p++;
							green = *buf_p++;
							red = *buf_p++;
							*pixbuf++ = red;
							*pixbuf++ = green;
							*pixbuf++ = blue;
							*pixbuf++ = 255;
							break;
						case 32:
							blue = *buf_p++;
							green = *buf_p++;
							red = *buf_p++;
							alphabyte = *buf_p++;
							*pixbuf++ = red;
							*pixbuf++ = green;
							*pixbuf++ = blue;
							*pixbuf++ = alphabyte;
							break;
						default:
							//Sysprintf("LoadTGA: illegal pixel_size '%d' in file '%s'\n", targa_header.pixel_size, name );
							break;
						}
						column++;
						if ( column == columns ) { // pixel packet run spans across rows
							column = 0;
							if ( row > 0 ) {
								row--;
							}
							else{
								goto breakOut;
							}
							pixbuf = targa_rgba + row * columns * 4;
						}
					}
				}
			}
breakOut:;
		}
	}

	/* fix vertically flipped image */
	if ( ( targa_header.attributes & ( 1 << 5 ) ) ) {
		int flip;
		for ( row = 0; row < .5f * rows; row++ )
		{
			for ( column = 0; column < columns; column++ )
			{
				flip = *( (int*)targa_rgba + row * columns + column );
				*( (int*)targa_rgba + row * columns + column ) = *( (int*)targa_rgba + ( ( rows - 1 ) - row ) * columns + column );
				*( (int*)targa_rgba + ( ( rows - 1 ) - row ) * columns + column ) = flip;
			}
		}
	}
}