#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int ssize_t ;
typedef  scalar_t__ sprite_index ;
struct TYPE_9__ {scalar_t__ z; scalar_t__ y; scalar_t__ x; } ;
struct TYPE_11__ {int /*<<< orphan*/  canvas; int /*<<< orphan*/  cell_width; int /*<<< orphan*/  cell_height; TYPE_1__ sprite_tracker; int /*<<< orphan*/  logical_dpi_y; int /*<<< orphan*/  logical_dpi_x; int /*<<< orphan*/  underline_thickness; int /*<<< orphan*/  underline_position; int /*<<< orphan*/  baseline; } ;
struct TYPE_10__ {int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; } ;
typedef  TYPE_2__ Region ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_3__ FontGroup ;
typedef  int /*<<< orphan*/  FONTS_DATA_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  PyErr_Print () ; 
 int /*<<< orphan*/ * PyLong_AsVoidPtr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PyObject_CallFunction (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyTuple_GET_ITEM (int /*<<< orphan*/ *,int) ; 
 int PyTuple_GET_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_CLEAR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_canvas (TYPE_3__*) ; 
 int /*<<< orphan*/  current_send_sprite_to_gpu (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_increment (TYPE_3__*,int*) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  prerender_function ; 
 int /*<<< orphan*/  render_alpha_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprite_map_set_error (int) ; 

__attribute__((used)) static inline void
send_prerendered_sprites(FontGroup *fg) {
    int error = 0;
    sprite_index x = 0, y = 0, z = 0;
    // blank cell
    clear_canvas(fg);
    current_send_sprite_to_gpu((FONTS_DATA_HANDLE)fg, x, y, z, fg->canvas);
    do_increment(fg, &error);
    if (error != 0) { sprite_map_set_error(error); PyErr_Print(); fatal("Failed"); }
    PyObject *args = PyObject_CallFunction(prerender_function, "IIIIIdd", fg->cell_width, fg->cell_height, fg->baseline, fg->underline_position, fg->underline_thickness, fg->logical_dpi_x, fg->logical_dpi_y);
    if (args == NULL) { PyErr_Print(); fatal("Failed to pre-render cells"); }
    for (ssize_t i = 0; i < PyTuple_GET_SIZE(args) - 1; i++) {
        x = fg->sprite_tracker.x; y = fg->sprite_tracker.y; z = fg->sprite_tracker.z;
        if (y > 0) { fatal("Too many pre-rendered sprites for your GPU or the font size is too large"); }
        do_increment(fg, &error);
        if (error != 0) { sprite_map_set_error(error); PyErr_Print(); fatal("Failed"); }
        uint8_t *alpha_mask = PyLong_AsVoidPtr(PyTuple_GET_ITEM(args, i));
        clear_canvas(fg);
        Region r = { .right = fg->cell_width, .bottom = fg->cell_height };
        render_alpha_mask(alpha_mask, fg->canvas, &r, &r, fg->cell_width, fg->cell_width);
        current_send_sprite_to_gpu((FONTS_DATA_HANDLE)fg, x, y, z, fg->canvas);
    }
    Py_CLEAR(args);
}