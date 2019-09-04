#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  error_exit; } ;
struct my_jpeg_error_mgr {int /*<<< orphan*/  setjmp_buffer; TYPE_2__ pub; } ;
struct jpeg_decompress_struct {int output_width; int output_components; int output_height; int output_scanline; int out_color_components; TYPE_1__* mem; int /*<<< orphan*/  err; } ;
typedef  int /*<<< orphan*/  j_common_ptr ;
struct TYPE_3__ {int /*<<< orphan*/ * (* alloc_sarray ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ;} ;
typedef  int /*<<< orphan*/ * JSAMPARRAY ;

/* Variables and functions */
 int /*<<< orphan*/  JPOOL_IMAGE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ errormsg ; 
 int /*<<< orphan*/  j_putGrayScanlineToRGB (int /*<<< orphan*/ ,int,unsigned char*,int) ; 
 int /*<<< orphan*/  j_putRGBAScanline (int /*<<< orphan*/ ,int,unsigned char*,int) ; 
 int /*<<< orphan*/  j_putRGBScanline (int /*<<< orphan*/ ,int,unsigned char*,int) ; 
 int /*<<< orphan*/  jpeg_buffer_src (struct jpeg_decompress_struct*,void*,int) ; 
 int /*<<< orphan*/  jpeg_create_decompress (struct jpeg_decompress_struct*) ; 
 int /*<<< orphan*/  jpeg_destroy_decompress (struct jpeg_decompress_struct*) ; 
 int /*<<< orphan*/  jpeg_finish_decompress (struct jpeg_decompress_struct*) ; 
 int /*<<< orphan*/  jpeg_read_header (struct jpeg_decompress_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jpeg_read_scanlines (struct jpeg_decompress_struct*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  jpeg_start_decompress (struct jpeg_decompress_struct*) ; 
 int /*<<< orphan*/  jpeg_std_error (TYPE_2__*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  my_jpeg_error_exit ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

int LoadJPGBuff( void *src_buffer, int src_size, unsigned char **pic, int *width, int *height ) {
	struct jpeg_decompress_struct cinfo;
	struct my_jpeg_error_mgr jerr;
	JSAMPARRAY buffer;
	int row_stride, size;

	cinfo.err = jpeg_std_error( &jerr.pub );
	jerr.pub.error_exit = my_jpeg_error_exit;

	if ( setjmp( jerr.setjmp_buffer ) ) {
		*pic = (unsigned char*)errormsg;
		jpeg_destroy_decompress( &cinfo );
		return -1;
	}

	jpeg_create_decompress( &cinfo );
	jpeg_buffer_src( &cinfo, src_buffer, src_size );
	jpeg_read_header( &cinfo, TRUE );
	jpeg_start_decompress( &cinfo );

	row_stride = cinfo.output_width * cinfo.output_components;

	size = cinfo.output_width * cinfo.output_height * 4;
	*width = cinfo.output_width;
	*height = cinfo.output_height;
	*pic = (unsigned char*)( malloc( size + 1 ) );
	memset( *pic, 0, size + 1 );

	buffer = ( *cinfo.mem->alloc_sarray )( ( j_common_ptr ) & cinfo, JPOOL_IMAGE, row_stride, 1 );

	while ( cinfo.output_scanline < cinfo.output_height )
	{
		jpeg_read_scanlines( &cinfo, buffer, 1 );

		if ( cinfo.out_color_components == 4 ) {
			j_putRGBAScanline( buffer[0], cinfo.output_width, *pic, cinfo.output_scanline - 1 );
		}
		else if ( cinfo.out_color_components == 3 ) {
			j_putRGBScanline( buffer[0], cinfo.output_width, *pic, cinfo.output_scanline - 1 );
		}
		else if ( cinfo.out_color_components == 1 ) {
			j_putGrayScanlineToRGB( buffer[0], cinfo.output_width, *pic, cinfo.output_scanline - 1 );
		}
	}

	jpeg_finish_decompress( &cinfo );
	jpeg_destroy_decompress( &cinfo );

	return 0;
}