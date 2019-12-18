#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int height; int stride; int /*<<< orphan*/ * bits; } ;
struct TYPE_5__ {scalar_t__ format; int planes; int h; int* pitches; int /*<<< orphan*/ ** pixels; } ;
typedef  TYPE_1__ SDL_VoutOverlay ;
typedef  TYPE_2__ ANativeWindow_Buffer ;

/* Variables and functions */
 int IJKMIN (int,int) ; 
 scalar_t__ SDL_FCC_RV16 ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  av_image_copy_plane (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int,int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int android_render_rgb_on_rgb(ANativeWindow_Buffer *out_buffer, const SDL_VoutOverlay *overlay, int bpp)
{
    // SDLTRACE("SDL_VoutAndroid: android_render_rgb_on_rgb(%p)", overlay);
    assert(overlay->format == SDL_FCC_RV16);
    assert(overlay->planes == 1);

    int min_height = IJKMIN(out_buffer->height, overlay->h);
    int dst_stride = out_buffer->stride;
    int src_line_size = overlay->pitches[0];
    int dst_line_size = dst_stride * bpp / 8;

    uint8_t *dst_pixels = out_buffer->bits;
    const uint8_t *src_pixels = overlay->pixels[0];

    if (dst_line_size == src_line_size) {
        int plane_size = src_line_size * min_height;
        // ALOGE("android_render_rgb_on_rgb (pix-match) %p %p %d", dst_pixels, src_pixels, plane_size);
        memcpy(dst_pixels, src_pixels, plane_size);
    } else {
        // TODO: 9 padding
        int bytewidth = IJKMIN(dst_line_size, src_line_size);

        // ALOGE("android_render_rgb_on_rgb (pix-mismatch) %p %d %p %d %d %d", dst_pixels, dst_line_size, src_pixels, src_line_size, bytewidth, min_height);
        av_image_copy_plane(dst_pixels, dst_line_size, src_pixels, src_line_size, bytewidth, min_height);
    }

    return 0;
}