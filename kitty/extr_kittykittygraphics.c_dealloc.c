#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  (* tp_free ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_6__ {size_t image_count; scalar_t__ render_data; scalar_t__ images; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ GraphicsManager ;

/* Variables and functions */
 TYPE_4__* Py_TYPE (TYPE_1__*) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  free_image (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dealloc(GraphicsManager* self) {
    size_t i;
    if (self->images) {
        for (i = 0; i < self->image_count; i++) free_image(self, self->images + i);
        free(self->images);
    }
    free(self->render_data);
    Py_TYPE(self)->tp_free((PyObject*)self);
}