#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int pixel ;
struct TYPE_15__ {TYPE_5__* glyph; int /*<<< orphan*/  height; int /*<<< orphan*/  max_advance_width; } ;
struct TYPE_11__ {int x; } ;
struct TYPE_14__ {TYPE_1__ advance; int /*<<< orphan*/  bitmap; } ;
struct TYPE_13__ {TYPE_9__* face; } ;
struct TYPE_12__ {size_t width; size_t height; unsigned char* canvas; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ StringCanvas ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  ProcessedBitmap ;
typedef  TYPE_3__ Face ;
typedef  int /*<<< orphan*/  FT_UInt ;
typedef  int /*<<< orphan*/  FT_Bitmap ;

/* Variables and functions */
 int /*<<< orphan*/  EMPTY_PBM ; 
 int /*<<< orphan*/  FT_Get_Char_Index (TYPE_9__*,char const) ; 
 int /*<<< orphan*/  FT_LOAD_DEFAULT ; 
 int FT_Load_Glyph (TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FT_RENDER_MODE_NORMAL ; 
 int FT_Render_Glyph (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int* calloc (size_t,int) ; 
 int font_units_to_pixels_x (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int font_units_to_pixels_y (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int*) ; 
 unsigned char* malloc (int) ; 
 int /*<<< orphan*/  place_bitmap_in_canvas (int*,int /*<<< orphan*/ *,size_t,size_t,size_t,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  populate_processed_bitmap (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 size_t strnlen (char const*,int) ; 

StringCanvas
render_simple_text_impl(PyObject *s, const char *text, unsigned int baseline) {
    Face *self = (Face*)s;
    StringCanvas ans = {0};
    size_t num_chars = strnlen(text, 32);
    int max_char_width = font_units_to_pixels_x(self, self->face->max_advance_width);
    size_t canvas_width = max_char_width * (num_chars*2);
    size_t canvas_height = font_units_to_pixels_y(self, self->face->height) + 8;
    pixel *canvas = calloc(canvas_width * canvas_height, sizeof(pixel));
    if (!canvas) return ans;
    size_t pen_x = 0;
    ProcessedBitmap pbm;
    for (size_t n = 0; n < num_chars; n++) {
        FT_UInt glyph_index = FT_Get_Char_Index(self->face, text[n]);
        int error = FT_Load_Glyph(self->face, glyph_index, FT_LOAD_DEFAULT);
        if (error) continue;
        error = FT_Render_Glyph(self->face->glyph, FT_RENDER_MODE_NORMAL);
        if (error) continue;
        FT_Bitmap *bitmap = &self->face->glyph->bitmap;
        pbm = EMPTY_PBM;
        populate_processed_bitmap(self->face->glyph, bitmap, &pbm, false);
        place_bitmap_in_canvas(canvas, &pbm, canvas_width, canvas_height, pen_x, 0, baseline);
        pen_x += self->face->glyph->advance.x >> 6;
    }
    ans.width = pen_x; ans.height = canvas_height;
    ans.canvas = malloc(ans.width * ans.height);
    if (ans.canvas) {
        for (size_t row = 0; row < ans.height; row++) {
            unsigned char *destp = ans.canvas + (ans.width * row);
            pixel *srcp = canvas + (canvas_width * row);
            for (size_t i = 0; i < ans.width; i++) destp[i] = srcp[i] & 0xff;
        }
    }
    free(canvas);
    return ans;
}