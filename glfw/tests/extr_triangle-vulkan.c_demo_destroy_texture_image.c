#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct texture_object {int /*<<< orphan*/  mem; int /*<<< orphan*/  image; } ;
struct demo {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  vkDestroyImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vkFreeMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void demo_destroy_texture_image(struct demo *demo,
                                       struct texture_object *tex_obj) {
    /* clean up staging resources */
    vkDestroyImage(demo->device, tex_obj->image, NULL);
    vkFreeMemory(demo->device, tex_obj->mem, NULL);
}