#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  sprite_position ;
typedef  int /*<<< orphan*/  pixel ;
typedef  int /*<<< orphan*/  hb_glyph_position_t ;
typedef  int /*<<< orphan*/  hb_glyph_info_t ;
typedef  int /*<<< orphan*/  glyph_index ;
struct TYPE_21__ {int /*<<< orphan*/  ch; } ;
struct TYPE_20__ {int /*<<< orphan*/  italic; int /*<<< orphan*/  bold; int /*<<< orphan*/  face; } ;
struct TYPE_19__ {int /*<<< orphan*/ * canvas; int /*<<< orphan*/  baseline; int /*<<< orphan*/  cell_height; int /*<<< orphan*/  cell_width; } ;
struct TYPE_18__ {int attrs; } ;
struct TYPE_17__ {int rendered; int colored; int /*<<< orphan*/  z; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ SpritePosition ;
typedef  TYPE_2__ GPUCell ;
typedef  TYPE_3__ FontGroup ;
typedef  TYPE_4__ Font ;
typedef  int /*<<< orphan*/  FONTS_DATA_HANDLE ;
typedef  int /*<<< orphan*/  ExtraGlyphs ;
typedef  TYPE_5__ CPUCell ;

/* Variables and functions */
 unsigned int MIN (int,unsigned int) ; 
 scalar_t__ PyErr_Occurred () ; 
 int /*<<< orphan*/  PyErr_Print () ; 
 int WIDTH_MASK ; 
 int /*<<< orphan*/  clear_canvas (TYPE_3__*) ; 
 int /*<<< orphan*/  current_send_sprite_to_gpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * extract_cell_from_canvas (TYPE_3__*,unsigned int,unsigned int) ; 
 scalar_t__ is_emoji (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  render_glyphs_in_cells (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_cell_sprite (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  sprite_map_set_error (int) ; 
 TYPE_1__* sprite_position_for (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static inline void
render_group(FontGroup *fg, unsigned int num_cells, unsigned int num_glyphs, CPUCell *cpu_cells, GPUCell *gpu_cells, hb_glyph_info_t *info, hb_glyph_position_t *positions, Font *font, glyph_index glyph, ExtraGlyphs *extra_glyphs, bool center_glyph) {
    static SpritePosition* sprite_position[16];
    int error = 0;
    num_cells = MIN(sizeof(sprite_position)/sizeof(sprite_position[0]), num_cells);
    for (unsigned int i = 0; i < num_cells; i++) {
        sprite_position[i] = sprite_position_for(fg, font, glyph, extra_glyphs, (uint8_t)i, &error);
        if (error != 0) { sprite_map_set_error(error); PyErr_Print(); return; }
    }
    if (sprite_position[0]->rendered) {
        for (unsigned int i = 0; i < num_cells; i++) { set_cell_sprite(gpu_cells + i, sprite_position[i]); }
        return;
    }

    clear_canvas(fg);
    bool was_colored = (gpu_cells->attrs & WIDTH_MASK) == 2 && is_emoji(cpu_cells->ch);
    render_glyphs_in_cells(font->face, font->bold, font->italic, info, positions, num_glyphs, fg->canvas, fg->cell_width, fg->cell_height, num_cells, fg->baseline, &was_colored, (FONTS_DATA_HANDLE)fg, center_glyph);
    if (PyErr_Occurred()) PyErr_Print();

    for (unsigned int i = 0; i < num_cells; i++) {
        sprite_position[i]->rendered = true;
        sprite_position[i]->colored = was_colored;
        set_cell_sprite(gpu_cells + i, sprite_position[i]);
        pixel *buf = num_cells == 1 ? fg->canvas : extract_cell_from_canvas(fg, i, num_cells);
        current_send_sprite_to_gpu((FONTS_DATA_HANDLE)fg, sprite_position[i]->x, sprite_position[i]->y, sprite_position[i]->z, buf);
    }

}