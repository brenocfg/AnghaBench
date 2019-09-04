#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  glyph_index ;
struct TYPE_20__ {int /*<<< orphan*/  ch; } ;
struct TYPE_15__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_19__ {TYPE_1__ member_0; } ;
struct TYPE_18__ {double logical_dpi_x; double logical_dpi_y; int /*<<< orphan*/  canvas; int /*<<< orphan*/  cell_width; int /*<<< orphan*/  cell_height; int /*<<< orphan*/ * fonts; } ;
struct TYPE_17__ {int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; } ;
struct TYPE_16__ {int rendered; int colored; int /*<<< orphan*/  z; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_2__ SpritePosition ;
typedef  TYPE_3__ Region ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  GPUCell ;
typedef  TYPE_4__ FontGroup ;
typedef  int /*<<< orphan*/  FONTS_DATA_HANDLE ;
typedef  TYPE_5__ ExtraGlyphs ;
typedef  TYPE_6__ CPUCell ;

/* Variables and functions */
 size_t BOX_FONT ; 
 int /*<<< orphan*/  PyErr_Print () ; 
 int /*<<< orphan*/ * PyLong_AsVoidPtr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PyObject_CallFunction (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  PyTuple_GET_ITEM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  box_drawing_function ; 
 int /*<<< orphan*/  box_glyph_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_canvas (TYPE_4__*) ; 
 int /*<<< orphan*/  current_send_sprite_to_gpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  render_alpha_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sprite (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprite_map_set_error (int) ; 
 TYPE_2__* sprite_position_for (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_5__*,int,int*) ; 

__attribute__((used)) static void
render_box_cell(FontGroup *fg, CPUCell *cpu_cell, GPUCell *gpu_cell) {
    int error = 0;
    glyph_index glyph = box_glyph_id(cpu_cell->ch);
    static ExtraGlyphs extra_glyphs = {{0}};
    SpritePosition *sp = sprite_position_for(fg, &fg->fonts[BOX_FONT], glyph, &extra_glyphs, false, &error);
    if (sp == NULL) {
        sprite_map_set_error(error); PyErr_Print();
        set_sprite(gpu_cell, 0, 0, 0);
        return;
    }
    set_sprite(gpu_cell, sp->x, sp->y, sp->z);
    if (sp->rendered) return;
    sp->rendered = true;
    sp->colored = false;
    PyObject *ret = PyObject_CallFunction(box_drawing_function, "IIId", cpu_cell->ch, fg->cell_width, fg->cell_height, (fg->logical_dpi_x + fg->logical_dpi_y) / 2.0);
    if (ret == NULL) { PyErr_Print(); return; }
    uint8_t *alpha_mask = PyLong_AsVoidPtr(PyTuple_GET_ITEM(ret, 0));
    clear_canvas(fg);
    Region r = { .right = fg->cell_width, .bottom = fg->cell_height };
    render_alpha_mask(alpha_mask, fg->canvas, &r, &r, fg->cell_width, fg->cell_width);
    current_send_sprite_to_gpu((FONTS_DATA_HANDLE)fg, sp->x, sp->y, sp->z, fg->canvas);
    Py_DECREF(ret);
}