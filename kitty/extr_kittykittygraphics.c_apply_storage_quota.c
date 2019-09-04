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
struct TYPE_5__ {size_t used_storage; scalar_t__ image_count; int /*<<< orphan*/  images; } ;
typedef  int /*<<< orphan*/  Image ;
typedef  TYPE_1__ GraphicsManager ;

/* Variables and functions */
 int /*<<< orphan*/  oldest_last ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_image (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  remove_images (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trim_predicate ; 

__attribute__((used)) static inline void
apply_storage_quota(GraphicsManager *self, size_t storage_limit, Image *currently_added_image) {
    // First remove unreferenced images, even if they have an id
    remove_images(self, trim_predicate, currently_added_image);
    if (self->used_storage < storage_limit) return;

    qsort(self->images, self->image_count, sizeof(Image), oldest_last);
    while (self->used_storage > storage_limit && self->image_count > 0) {
        remove_image(self, self->image_count - 1);
    }
    if (!self->image_count) self->used_storage = 0;  // sanity check
}