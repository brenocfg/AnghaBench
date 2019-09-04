#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ pixel_mode; unsigned int width; int /*<<< orphan*/  rows; int /*<<< orphan*/  pitch; int /*<<< orphan*/  buffer; } ;
struct TYPE_17__ {TYPE_11__* face; int /*<<< orphan*/  ydpi; int /*<<< orphan*/  xdpi; int /*<<< orphan*/  char_height; } ;
struct TYPE_16__ {unsigned int width; scalar_t__ pixel_mode; float bitmap_top; float factor; float bitmap_left; int /*<<< orphan*/  rows; int /*<<< orphan*/  stride; scalar_t__ start_x; int /*<<< orphan*/  buf; } ;
struct TYPE_15__ {scalar_t__ bitmap_left; scalar_t__ bitmap_top; TYPE_5__ bitmap; } ;
struct TYPE_14__ {unsigned short width; } ;
struct TYPE_13__ {short num_fixed_sizes; TYPE_2__* glyph; TYPE_1__* available_sizes; } ;
typedef  TYPE_3__ ProcessedBitmap ;
typedef  TYPE_4__ Face ;
typedef  scalar_t__ FT_Error ;
typedef  TYPE_5__ FT_Bitmap ;

/* Variables and functions */
 int /*<<< orphan*/  FT_LOAD_COLOR ; 
 scalar_t__ FT_PIXEL_MODE_BGRA ; 
 scalar_t__ FT_Select_Size (TYPE_11__*,unsigned short) ; 
 int /*<<< orphan*/  FT_Set_Char_Size (TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned short USHRT_MAX ; 
 int /*<<< orphan*/  detect_right_edge (TYPE_3__*) ; 
 int /*<<< orphan*/  downsample_bitmap (TYPE_3__*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  load_glyph (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_freetype_error (char*,scalar_t__) ; 

__attribute__((used)) static inline bool
render_color_bitmap(Face *self, int glyph_id, ProcessedBitmap *ans, unsigned int cell_width, unsigned int cell_height, unsigned int num_cells, unsigned int baseline) {
    (void)baseline;
    unsigned short best = 0, diff = USHRT_MAX;
    for (short i = 0; i < self->face->num_fixed_sizes; i++) {
        unsigned short w = self->face->available_sizes[i].width;
        unsigned short d = w > (unsigned short)cell_width ? w - (unsigned short)cell_width : (unsigned short)cell_width - w;
        if (d < diff) {
            diff = d;
            best = i;
        }
    }
    FT_Error error = FT_Select_Size(self->face, best);
    if (error) { set_freetype_error("Failed to set char size for non-scalable font, with error:", error); return false; }
    if (!load_glyph(self, glyph_id, FT_LOAD_COLOR)) return false;
    FT_Set_Char_Size(self->face, 0, self->char_height, self->xdpi, self->ydpi);
    FT_Bitmap *bitmap = &self->face->glyph->bitmap;
    if (bitmap->pixel_mode != FT_PIXEL_MODE_BGRA) return false;
    ans->buf = bitmap->buffer;
    ans->start_x = 0; ans->width = bitmap->width;
    ans->stride = bitmap->pitch < 0 ? -bitmap->pitch : bitmap->pitch;
    ans->rows = bitmap->rows;
    ans->pixel_mode = bitmap->pixel_mode;
    if (ans->width > num_cells * cell_width + 2) downsample_bitmap(ans, num_cells * cell_width, cell_height);
    ans->bitmap_top = (float)self->face->glyph->bitmap_top / ans->factor;
    ans->bitmap_left = (float)self->face->glyph->bitmap_left / ans->factor;
    detect_right_edge(ans);
    return true;
}