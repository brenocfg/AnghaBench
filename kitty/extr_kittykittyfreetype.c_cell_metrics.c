#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int ascender; unsigned int underline_position; unsigned int underline_thickness; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ Face ;

/* Variables and functions */
 unsigned int CALC_CELL_HEIGHT (TYPE_1__*) ; 
 unsigned int MAX (int,unsigned int) ; 
 unsigned int MIN (unsigned int,unsigned int) ; 
 unsigned int calc_cell_width (TYPE_1__*) ; 
 unsigned int font_units_to_pixels_y (TYPE_1__*,unsigned int) ; 

void
cell_metrics(PyObject *s, unsigned int* cell_width, unsigned int* cell_height, unsigned int* baseline, unsigned int* underline_position, unsigned int* underline_thickness) {
    Face *self = (Face*)s;
    *cell_width = calc_cell_width(self);
    *cell_height = CALC_CELL_HEIGHT(self);
    *baseline = font_units_to_pixels_y(self, self->ascender);
    *underline_position = MIN(*cell_height - 1, (unsigned int)font_units_to_pixels_y(self, MAX(0, self->ascender - self->underline_position)));
    *underline_thickness = MAX(1, font_units_to_pixels_y(self, self->underline_thickness));
}