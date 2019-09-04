#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  (* tp_free ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  path; scalar_t__ extra_data; int /*<<< orphan*/  (* free_extra_data ) (scalar_t__) ;scalar_t__ face; scalar_t__ harfbuzz_font; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ Face ;

/* Variables and functions */
 int /*<<< orphan*/  FT_Done_Face (scalar_t__) ; 
 int /*<<< orphan*/  Py_CLEAR (int /*<<< orphan*/ ) ; 
 TYPE_3__* Py_TYPE (TYPE_1__*) ; 
 int /*<<< orphan*/  hb_font_destroy (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dealloc(Face* self) {
    if (self->harfbuzz_font) hb_font_destroy(self->harfbuzz_font);
    if (self->face) FT_Done_Face(self->face);
    if (self->extra_data && self->free_extra_data) self->free_extra_data(self->extra_data);
    Py_CLEAR(self->path);
    Py_TYPE(self)->tp_free((PyObject*)self);
}