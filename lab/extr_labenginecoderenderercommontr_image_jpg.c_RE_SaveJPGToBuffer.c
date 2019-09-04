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
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct jpeg_compress_struct {int image_width; int image_height; int input_components; int next_scanline; scalar_t__ dest; TYPE_1__* comp_info; int /*<<< orphan*/  in_color_space; TYPE_6__* err; } ;
struct TYPE_9__ {int /*<<< orphan*/  setjmp_buffer; int /*<<< orphan*/  pub; } ;
typedef  TYPE_3__ q_jpeg_error_mgr_t ;
typedef  TYPE_4__* my_dest_ptr ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_12__ {int /*<<< orphan*/  output_message; int /*<<< orphan*/  error_exit; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* Printf ) (int /*<<< orphan*/ ,char*) ;} ;
struct TYPE_8__ {size_t free_in_buffer; } ;
struct TYPE_10__ {size_t size; TYPE_2__ pub; } ;
struct TYPE_7__ {int h_samp_factor; int v_samp_factor; } ;
typedef  int /*<<< orphan*/ * JSAMPROW ;

/* Variables and functions */
 int /*<<< orphan*/  JCS_RGB ; 
 int /*<<< orphan*/  PRINT_ALL ; 
 int /*<<< orphan*/  R_JPGErrorExit ; 
 int /*<<< orphan*/  R_JPGOutputMessage ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  jpegDest (struct jpeg_compress_struct*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  jpeg_create_compress (struct jpeg_compress_struct*) ; 
 int /*<<< orphan*/  jpeg_destroy_compress (struct jpeg_compress_struct*) ; 
 int /*<<< orphan*/  jpeg_finish_compress (struct jpeg_compress_struct*) ; 
 int /*<<< orphan*/  jpeg_set_defaults (struct jpeg_compress_struct*) ; 
 int /*<<< orphan*/  jpeg_set_quality (struct jpeg_compress_struct*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jpeg_start_compress (struct jpeg_compress_struct*,int /*<<< orphan*/ ) ; 
 TYPE_6__* jpeg_std_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jpeg_write_scanlines (struct jpeg_compress_struct*,int /*<<< orphan*/ **,int) ; 
 TYPE_5__ ri ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 

size_t RE_SaveJPGToBuffer(byte *buffer, size_t bufSize, int quality,
    int image_width, int image_height, byte *image_buffer, int padding)
{
  struct jpeg_compress_struct cinfo;
  q_jpeg_error_mgr_t jerr;
  JSAMPROW row_pointer[1];	/* pointer to JSAMPLE row[s] */
  my_dest_ptr dest;
  int row_stride;		/* physical row width in image buffer */
  size_t outcount;

  /* Step 1: allocate and initialize JPEG compression object */
  cinfo.err = jpeg_std_error(&jerr.pub);
  cinfo.err->error_exit = R_JPGErrorExit;
  cinfo.err->output_message = R_JPGOutputMessage;

  /* Establish the setjmp return context for R_JPGErrorExit to use. */
  if (setjmp(jerr.setjmp_buffer))
  {
    /* If we get here, the JPEG code has signaled an error.
     * We need to clean up the JPEG object and return.
     */
    jpeg_destroy_compress(&cinfo);

    ri.Printf(PRINT_ALL, "\n");
    return 0;
  }

  /* Now we can initialize the JPEG compression object. */
  jpeg_create_compress(&cinfo);

  /* Step 2: specify data destination (eg, a file) */
  /* Note: steps 2 and 3 can be done in either order. */
  jpegDest(&cinfo, buffer, bufSize);

  /* Step 3: set parameters for compression */
  cinfo.image_width = image_width; 	/* image width and height, in pixels */
  cinfo.image_height = image_height;
  cinfo.input_components = 3;		/* # of color components per pixel */
  cinfo.in_color_space = JCS_RGB; 	/* colorspace of input image */

  jpeg_set_defaults(&cinfo);
  jpeg_set_quality(&cinfo, quality, TRUE /* limit to baseline-JPEG values */);
  /* If quality is set high, disable chroma subsampling */
  if (quality >= 85) {
    cinfo.comp_info[0].h_samp_factor = 1;
    cinfo.comp_info[0].v_samp_factor = 1;
  }

  /* Step 4: Start compressor */
  jpeg_start_compress(&cinfo, TRUE);

  /* Step 5: while (scan lines remain to be written) */
  /*           jpeg_write_scanlines(...); */
  row_stride = image_width * cinfo.input_components + padding; /* JSAMPLEs per row in image_buffer */
  
  while (cinfo.next_scanline < cinfo.image_height) {
    /* jpeg_write_scanlines expects an array of pointers to scanlines.
     * Here the array is only one element long, but you could pass
     * more than one scanline at a time if that's more convenient.
     */
    row_pointer[0] = &image_buffer[((cinfo.image_height-1)*row_stride)-cinfo.next_scanline * row_stride];
    (void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
  }

  /* Step 6: Finish compression */
  jpeg_finish_compress(&cinfo);
  
  dest = (my_dest_ptr) cinfo.dest;
  outcount = dest->size - dest->pub.free_in_buffer;
 
  /* Step 7: release JPEG compression object */
  jpeg_destroy_compress(&cinfo);

  /* And we're done! */
  return outcount;
}