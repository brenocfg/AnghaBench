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
struct TYPE_4__ {size_t image_count; int /*<<< orphan*/ * images; } ;
typedef  int /*<<< orphan*/  Image ;
typedef  TYPE_1__ GraphicsManager ;

/* Variables and functions */
 int /*<<< orphan*/  remove_image (TYPE_1__*,size_t) ; 

__attribute__((used)) static inline void
remove_images(GraphicsManager *self, bool(*predicate)(Image*), Image* skip_image) {
    for (size_t i = self->image_count; i-- > 0;) {
        Image *img = self->images + i;
        if (img != skip_image && predicate(img)) {
            remove_image(self, i);
        }
    }
}