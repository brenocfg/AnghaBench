#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int layers_dirty; int /*<<< orphan*/  image_count; scalar_t__ images; } ;
typedef  int /*<<< orphan*/  Image ;
typedef  TYPE_1__ GraphicsManager ;

/* Variables and functions */
 int /*<<< orphan*/  free_image (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  remove_from_array (scalar_t__,int,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
remove_image(GraphicsManager *self, size_t idx) {
    free_image(self, self->images + idx);
    remove_from_array(self->images, sizeof(Image), idx, self->image_count--);
    self->layers_dirty = true;
}