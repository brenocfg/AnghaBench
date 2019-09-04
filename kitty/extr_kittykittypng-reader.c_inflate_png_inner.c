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
typedef  int /*<<< orphan*/  uint8_t ;
struct fake_file {size_t sz; int /*<<< orphan*/  const* buf; } ;
struct custom_error_handler {int /*<<< orphan*/  jb; int /*<<< orphan*/  err_handler; } ;
typedef  int /*<<< orphan*/ * png_structp ;
struct TYPE_3__ {int height; int sz; int ok; int /*<<< orphan*/ ** row_pointers; int /*<<< orphan*/ * decompressed; int /*<<< orphan*/  width; int /*<<< orphan*/  err_handler; } ;
typedef  TYPE_1__ png_read_data ;
typedef  int /*<<< orphan*/ * png_infop ;
typedef  int /*<<< orphan*/  png_bytep ;
typedef  int png_byte ;

/* Variables and functions */
 int /*<<< orphan*/  ABRT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int PNG_COLOR_TYPE_GRAY ; 
 int PNG_COLOR_TYPE_GRAY_ALPHA ; 
 int PNG_COLOR_TYPE_PALETTE ; 
 int PNG_COLOR_TYPE_RGB ; 
 int /*<<< orphan*/  PNG_FILLER_AFTER ; 
 int /*<<< orphan*/  PNG_INFO_tRNS ; 
 int /*<<< orphan*/  PNG_LIBPNG_VER_STRING ; 
 void* malloc (int) ; 
 int /*<<< orphan*/ * png_create_info_struct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * png_create_read_struct (int /*<<< orphan*/ ,struct custom_error_handler*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_destroy_read_struct (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int png_get_bit_depth (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int png_get_color_type (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int png_get_image_height (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_get_image_width (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int png_get_rowbytes (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ png_get_valid (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_read_image (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  png_read_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_read_update_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_set_expand_gray_1_2_4_to_8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_set_filler (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_set_gray_to_rgb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_set_palette_to_rgb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_set_read_fn (int /*<<< orphan*/ *,struct fake_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_set_strip_16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_set_tRNS_to_alpha (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_png_error_handler ; 
 int /*<<< orphan*/  read_png_from_buffer ; 
 int /*<<< orphan*/  read_png_warn_handler ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 

void
inflate_png_inner(png_read_data *d, const uint8_t *buf, size_t bufsz) {
    struct fake_file f = {.buf = buf, .sz = bufsz};
    png_structp png = NULL;
    png_infop info = NULL;
    struct custom_error_handler eh = {.err_handler = d->err_handler};
    png = png_create_read_struct(PNG_LIBPNG_VER_STRING, &eh, read_png_error_handler, read_png_warn_handler);
    if (!png) ABRT(ENOMEM, "Failed to create PNG read structure");
    info = png_create_info_struct(png);
    if (!info) ABRT(ENOMEM, "Failed to create PNG info structure");

    if (setjmp(eh.jb)) goto err;

    png_set_read_fn(png, &f, read_png_from_buffer);
    png_read_info(png, info);
    png_byte color_type, bit_depth;
    d->width      = png_get_image_width(png, info);
    d->height     = png_get_image_height(png, info);
    color_type = png_get_color_type(png, info);
    bit_depth  = png_get_bit_depth(png, info);

    // Ensure we get RGBA data out of libpng
    if (bit_depth == 16) png_set_strip_16(png);
    if (color_type == PNG_COLOR_TYPE_PALETTE) png_set_palette_to_rgb(png);
    // PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth.
    if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) png_set_expand_gray_1_2_4_to_8(png);

    if (png_get_valid(png, info, PNG_INFO_tRNS)) png_set_tRNS_to_alpha(png);

    // These color_type don't have an alpha channel then fill it with 0xff.
    if (color_type == PNG_COLOR_TYPE_RGB || color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_PALETTE) png_set_filler(png, 0xFF, PNG_FILLER_AFTER);

    if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA) png_set_gray_to_rgb(png);
    png_read_update_info(png, info);

    int rowbytes = png_get_rowbytes(png, info);
    d->sz = rowbytes * d->height * sizeof(png_byte);
    d->decompressed = malloc(d->sz + 16);
    if (d->decompressed == NULL) ABRT(ENOMEM, "Out of memory allocating decompression buffer for PNG");
    d->row_pointers = malloc(d->height * sizeof(png_bytep));
    if (d->row_pointers == NULL) ABRT(ENOMEM, "Out of memory allocating row_pointers buffer for PNG");
    for (int i = 0; i < d->height; i++) d->row_pointers[i] = d->decompressed + i * rowbytes;
    png_read_image(png, d->row_pointers);

    d->ok = true;
err:
    if (png) png_destroy_read_struct(&png, info ? &info : NULL, NULL);
    return;
}