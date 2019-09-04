#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ (* tp_alloc ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {int images_capacity; int capacity; int /*<<< orphan*/ * render_data; int /*<<< orphan*/ * images; } ;
typedef  int /*<<< orphan*/  ImageRenderData ;
typedef  int /*<<< orphan*/  Image ;
typedef  TYPE_1__ GraphicsManager ;

/* Variables and functions */
 TYPE_2__ GraphicsManager_Type ; 
 int /*<<< orphan*/  PyErr_NoMemory () ; 
 int /*<<< orphan*/  Py_CLEAR (TYPE_1__*) ; 
 void* calloc (int,int) ; 
 scalar_t__ stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

GraphicsManager*
grman_alloc() {
    GraphicsManager *self = (GraphicsManager *)GraphicsManager_Type.tp_alloc(&GraphicsManager_Type, 0);
    self->images_capacity = 64;
    self->images = calloc(self->images_capacity, sizeof(Image));
    self->capacity = 64;
    self->render_data = calloc(self->capacity, sizeof(ImageRenderData));
    if (self->images == NULL || self->render_data == NULL) {
        PyErr_NoMemory();
        Py_CLEAR(self); return NULL;
    }
    return self;
}