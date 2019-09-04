#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  glyph_index ;
struct TYPE_11__ {TYPE_3__* face; } ;
struct TYPE_8__ {int width; } ;
struct TYPE_7__ {int width; } ;
struct TYPE_10__ {TYPE_2__ metrics; TYPE_1__ bitmap; } ;
struct TYPE_9__ {TYPE_4__* glyph; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_5__ Face ;

/* Variables and functions */
 int /*<<< orphan*/  FT_LOAD_DEFAULT ; 
 int /*<<< orphan*/  PyErr_Print () ; 
 int /*<<< orphan*/  load_glyph (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
get_glyph_width(PyObject *s, glyph_index g) {
    Face *self = (Face*)s;
    if (!load_glyph(self, g, FT_LOAD_DEFAULT)) { PyErr_Print(); return false; }
#define M self->face->glyph->metrics
#define B self->face->glyph->bitmap
    /* printf("glyph: %u bitmap.width: %d bitmap.rows: %d horiAdvance: %ld horiBearingX: %ld horiBearingY: %ld vertBearingX: %ld vertBearingY: %ld vertAdvance: %ld width: %ld height: %ld\n", */
    /*         g, B.width, B.rows, M.horiAdvance, M.horiBearingX, M.horiBearingY, M.vertBearingX, M.vertBearingY, M.vertAdvance, M.width, M.height); */
    return B.width ? B.width : (M.width / 64);
#undef M
#undef B
}