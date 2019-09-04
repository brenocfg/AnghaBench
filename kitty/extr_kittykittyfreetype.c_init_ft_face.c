#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int face_index; int /*<<< orphan*/  underline_thickness; int /*<<< orphan*/  underline_position; int /*<<< orphan*/  max_advance_height; int /*<<< orphan*/  max_advance_width; int /*<<< orphan*/  height; int /*<<< orphan*/  descender; int /*<<< orphan*/  ascender; int /*<<< orphan*/  units_per_EM; } ;
struct TYPE_6__ {int hinting; int hintstyle; int index; TYPE_3__* face; int /*<<< orphan*/ * path; int /*<<< orphan*/ * harfbuzz_font; int /*<<< orphan*/  has_color; int /*<<< orphan*/  is_scalable; int /*<<< orphan*/  underline_thickness; int /*<<< orphan*/  underline_position; int /*<<< orphan*/  max_advance_height; int /*<<< orphan*/  max_advance_width; int /*<<< orphan*/  height; int /*<<< orphan*/  descender; int /*<<< orphan*/  ascender; int /*<<< orphan*/  units_per_EM; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ Face ;
typedef  int /*<<< orphan*/  FONTS_DATA_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  FT_HAS_COLOR (TYPE_3__*) ; 
 int /*<<< orphan*/  FT_IS_SCALABLE (TYPE_3__*) ; 
 int /*<<< orphan*/  FT_LOAD_DEFAULT ; 
 int /*<<< orphan*/  PyErr_NoMemory () ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_load_flags (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hb_ft_font_create (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_ft_font_set_load_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_size_for_face (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
init_ft_face(Face *self, PyObject *path, int hinting, int hintstyle, FONTS_DATA_HANDLE fg) {
#define CPY(n) self->n = self->face->n;
    CPY(units_per_EM); CPY(ascender); CPY(descender); CPY(height); CPY(max_advance_width); CPY(max_advance_height); CPY(underline_position); CPY(underline_thickness);
#undef CPY
    self->is_scalable = FT_IS_SCALABLE(self->face);
    self->has_color = FT_HAS_COLOR(self->face);
    self->hinting = hinting; self->hintstyle = hintstyle;
    if (!set_size_for_face((PyObject*)self, 0, false, fg)) return false;
    self->harfbuzz_font = hb_ft_font_create(self->face, NULL);
    if (self->harfbuzz_font == NULL) { PyErr_NoMemory(); return false; }
    hb_ft_font_set_load_flags(self->harfbuzz_font, get_load_flags(self->hinting, self->hintstyle, FT_LOAD_DEFAULT));

    self->path = path;
    Py_INCREF(self->path);
    self->index = self->face->face_index & 0xFFFF;
    return true;
}