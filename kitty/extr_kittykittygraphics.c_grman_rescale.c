#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ height; scalar_t__ width; } ;
struct TYPE_11__ {int layers_dirty; size_t image_count; TYPE_2__* images; } ;
struct TYPE_10__ {size_t refcnt; TYPE_1__* refs; } ;
struct TYPE_9__ {int /*<<< orphan*/  num_rows; int /*<<< orphan*/  num_cols; void* cell_y_offset; void* cell_x_offset; } ;
typedef  TYPE_1__ ImageRef ;
typedef  TYPE_2__ Image ;
typedef  TYPE_3__ GraphicsManager ;
typedef  TYPE_4__ CellPixelSize ;

/* Variables and functions */
 void* MIN (void*,scalar_t__) ; 
 int /*<<< orphan*/  update_dest_rect (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__) ; 

void
grman_rescale(GraphicsManager *self, CellPixelSize cell) {
    ImageRef *ref; Image *img;
    self->layers_dirty = true;
    for (size_t i = self->image_count; i-- > 0;) {
        img = self->images + i;
        for (size_t j = img->refcnt; j-- > 0;) {
            ref = img->refs + j;
            ref->cell_x_offset = MIN(ref->cell_x_offset, cell.width - 1);
            ref->cell_y_offset = MIN(ref->cell_y_offset, cell.height - 1);
            update_dest_rect(ref, ref->num_cols, ref->num_rows, cell);
        }
    }
}