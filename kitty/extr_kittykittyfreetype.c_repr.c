#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* family_name; char* style_name; } ;
struct TYPE_4__ {int /*<<< orphan*/  underline_thickness; int /*<<< orphan*/  underline_position; int /*<<< orphan*/  height; int /*<<< orphan*/  descender; int /*<<< orphan*/  ascender; scalar_t__ has_color; scalar_t__ is_scalable; int /*<<< orphan*/  index; int /*<<< orphan*/  path; TYPE_3__* face; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ Face ;

/* Variables and functions */
 char* FT_Get_Postscript_Name (TYPE_3__*) ; 
 int /*<<< orphan*/ * PyUnicode_FromFormat (char*,char*,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_False ; 
 int /*<<< orphan*/  Py_True ; 

__attribute__((used)) static PyObject *
repr(Face *self) {
    const char *ps_name = FT_Get_Postscript_Name(self->face);
    return PyUnicode_FromFormat(
        "Face(family=%s, style=%s, ps_name=%s, path=%S, index=%d, is_scalable=%S, has_color=%S, ascender=%i, descender=%i, height=%i, underline_position=%i, underline_thickness=%i)",
        self->face->family_name ? self->face->family_name : "", self->face->style_name ? self->face->style_name : "",
        ps_name ? ps_name: "",
        self->path, self->index, self->is_scalable ? Py_True : Py_False, self->has_color ? Py_True : Py_False,
        self->ascender, self->descender, self->height, self->underline_position, self->underline_thickness
    );
}