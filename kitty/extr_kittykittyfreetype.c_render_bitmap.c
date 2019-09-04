#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_11__ ;

/* Type definitions */
struct TYPE_25__ {int /*<<< orphan*/  cell_height; } ;
struct TYPE_24__ {scalar_t__ pixel_mode; int num_grays; unsigned int pitch; unsigned int rows; unsigned int width; int* buffer; } ;
struct TYPE_23__ {int /*<<< orphan*/  ydpi; int /*<<< orphan*/  xdpi; scalar_t__ char_height; scalar_t__ char_width; scalar_t__ is_scalable; TYPE_1__* face; } ;
struct TYPE_22__ {unsigned int width; } ;
struct TYPE_21__ {TYPE_11__* glyph; } ;
struct TYPE_20__ {TYPE_4__ bitmap; } ;
typedef  TYPE_2__ ProcessedBitmap ;
typedef  TYPE_3__ Face ;
typedef  scalar_t__ FT_F26Dot6 ;
typedef  TYPE_4__ FT_Bitmap ;
typedef  TYPE_5__* FONTS_DATA_HANDLE ;

/* Variables and functions */
 int FT_Bitmap_Convert (int /*<<< orphan*/ ,TYPE_4__*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  FT_Bitmap_Done (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  FT_Bitmap_Init (TYPE_4__*) ; 
 int /*<<< orphan*/  FT_LOAD_RENDER ; 
 scalar_t__ FT_PIXEL_MODE_MONO ; 
 int /*<<< orphan*/  free_processed_bitmap (TYPE_2__*) ; 
 int /*<<< orphan*/  library ; 
 int /*<<< orphan*/  load_glyph (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  populate_processed_bitmap (TYPE_11__*,TYPE_4__*,TYPE_2__*,int) ; 
 scalar_t__ set_font_size (TYPE_3__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_freetype_error (char*,int) ; 
 int /*<<< orphan*/  trim_borders (TYPE_2__*,size_t) ; 

__attribute__((used)) static inline bool
render_bitmap(Face *self, int glyph_id, ProcessedBitmap *ans, unsigned int cell_width, unsigned int cell_height, unsigned int num_cells, bool bold, bool italic, bool rescale, FONTS_DATA_HANDLE fg) {
    if (!load_glyph(self, glyph_id, FT_LOAD_RENDER)) return false;
    unsigned int max_width = cell_width * num_cells;

    // Embedded bitmap glyph?
    if (self->face->glyph->bitmap.pixel_mode == FT_PIXEL_MODE_MONO) {
        FT_Bitmap bitmap;
        FT_Bitmap_Init(&bitmap);

        // This also sets pixel_mode to FT_PIXEL_MODE_GRAY so we don't have to
        int error = FT_Bitmap_Convert(library, &self->face->glyph->bitmap, &bitmap, 1);
        if (error) { set_freetype_error("Failed to convert bitmap, with error:", error); return false; }

        // Normalize gray levels to the range [0..255]
        bitmap.num_grays = 256;
        unsigned int stride = bitmap.pitch < 0 ? -bitmap.pitch : bitmap.pitch;
        for (unsigned int i = 0; i < bitmap.rows; ++i) {
            // We only have 2 levels
            for (unsigned int j = 0; j < bitmap.width; ++j) bitmap.buffer[i * stride + j] *= 255;
        }
        populate_processed_bitmap(self->face->glyph, &bitmap, ans, true);
        FT_Bitmap_Done(library, &bitmap);
    } else {
        populate_processed_bitmap(self->face->glyph, &self->face->glyph->bitmap, ans, false);
    }

    if (ans->width > max_width) {
        size_t extra = ans->width - max_width;
        if (italic && extra < cell_width / 2) {
            trim_borders(ans, extra);
        } else if (extra == 2 && num_cells == 1) {
            // there exist fonts that have bitmaps just a couple of pixels
            // wider than their advances, rather than rescale, which looks
            // bad, we just crop the bitmap on the right. See https://github.com/kovidgoyal/kitty/issues/352
        } else if (rescale && self->is_scalable && extra > 1) {
            FT_F26Dot6 char_width = self->char_width, char_height = self->char_height;
            float ar = (float)max_width / (float)ans->width;
            if (set_font_size(self, (FT_F26Dot6)((float)self->char_width * ar), (FT_F26Dot6)((float)self->char_height * ar), self->xdpi, self->ydpi, 0, fg->cell_height)) {
                free_processed_bitmap(ans);
                if (!render_bitmap(self, glyph_id, ans, cell_width, cell_height, num_cells, bold, italic, false, fg)) return false;
                if (!set_font_size(self, char_width, char_height, self->xdpi, self->ydpi, 0, fg->cell_height)) return false;
            } else return false;
        }
    }
    return true;
}