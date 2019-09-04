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
typedef  int png_uint_32 ;
typedef  int /*<<< orphan*/  png_struct ;
typedef  int /*<<< orphan*/  png_info ;
struct TYPE_2__ {int size; scalar_t__ offset; int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_1__ pngBuffer_t ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int /*<<< orphan*/  PNGReadData ; 
 int PNG_COLOR_TYPE_GRAY ; 
 int PNG_COLOR_TYPE_PALETTE ; 
 int PNG_COLOR_TYPE_RGB ; 
 int /*<<< orphan*/  PNG_FILLER_AFTER ; 
 int /*<<< orphan*/  PNG_INFO_tRNS ; 
 int /*<<< orphan*/  PNG_LIBPNG_VER_STRING ; 
 int /*<<< orphan*/  SYS_WRN ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * png_create_info_struct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * png_create_read_struct (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_destroy_read_struct (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  png_get_IHDR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int*,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int png_get_channels (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ png_get_valid (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_jmpbuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_read_image (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  png_read_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_set_expand (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_set_filler (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_set_read_fn (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_set_strip_16 (int /*<<< orphan*/ *) ; 
 scalar_t__ png_sig_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 void* safe_malloc (int) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void LoadPNGBuffer( byte *buffer, int size, byte **pixels, int *width, int *height ){
	png_struct  *png;
	png_info    *info, *end;
    pngBuffer_t pb;
	int i, bitDepth, colorType, channels;
	png_uint_32 w, h;
	byte        **rowPointers;

	/* dummy check */
	if ( buffer == NULL || size <= 0 || pixels == NULL || width == NULL || height == NULL ) {
		return;
	}

	/* null out */
	*pixels = 0;
	*width = 0;
	*height = 0;

	/* determine if this is a png file */
	if ( png_sig_cmp( buffer, 0, 8 ) != 0 ) {
		Sys_FPrintf( SYS_WRN, "WARNING: Invalid PNG file\n" );
		return;
	}

	/* create png structs */
	png = png_create_read_struct( PNG_LIBPNG_VER_STRING, NULL, NULL, NULL );
	if ( png == NULL ) {
		Sys_FPrintf( SYS_WRN, "WARNING: Unable to create PNG read struct\n" );
		return;
	}

	info = png_create_info_struct( png );
	if ( info == NULL ) {
		Sys_FPrintf( SYS_WRN, "WARNING: Unable to create PNG info struct\n" );
		png_destroy_read_struct( &png, NULL, NULL );
		return;
	}

	end = png_create_info_struct( png );
	if ( end == NULL ) {
		Sys_FPrintf( SYS_WRN, "WARNING: Unable to create PNG end info struct\n" );
		png_destroy_read_struct( &png, &info, NULL );
		return;
	}

	/* set read callback */
    pb.buffer = buffer;
    pb.size = size;
    pb.offset = 0;
	png_set_read_fn( png, (void*)&pb, PNGReadData );

	/* set error longjmp */
	if ( setjmp( png_jmpbuf(png) ) ) {
		Sys_FPrintf( SYS_WRN, "WARNING: An error occurred reading PNG image\n" );
		png_destroy_read_struct( &png, &info, &end );
		return;
	}

	/* fixme: add proper i/o stuff here */

	/* read png info */
	png_read_info( png, info );

	/* read image header chunk */
	png_get_IHDR( png, info,
				  &w, &h, &bitDepth, &colorType, NULL, NULL, NULL );

	/* read number of channels */
	channels = png_get_channels( png, info );

	/* the following will probably bork on certain types of png images, but hey... */

	/* force indexed/gray/trans chunk to rgb */
	if ( ( colorType == PNG_COLOR_TYPE_PALETTE && bitDepth <= 8 ) ||
		 ( colorType == PNG_COLOR_TYPE_GRAY && bitDepth <= 8 ) ||
		 png_get_valid( png, info, PNG_INFO_tRNS ) ) {
		png_set_expand( png );
	}

	/* strip 16bpc -> 8bpc */
	if ( bitDepth == 16 ) {
		png_set_strip_16( png );
	}

	/* pad rgb to rgba */
	if ( bitDepth == 8 && colorType == PNG_COLOR_TYPE_RGB ) {
		png_set_filler( png, 255, PNG_FILLER_AFTER );
	}

	/* create image pixel buffer */
	*width = w;
	*height = h;
	*pixels = safe_malloc( w * h * 4 );

	/* create row pointers */
	rowPointers = safe_malloc( h * sizeof( byte* ) );
	for ( i = 0; i < h; i++ )
		rowPointers[ i ] = *pixels + ( i * w * 4 );

	/* read the png */
	png_read_image( png, rowPointers );

	/* clean up */
	free( rowPointers );
	png_destroy_read_struct( &png, &info, &end );

}