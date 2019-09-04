#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int z_index; int image_id; } ;
typedef  TYPE_1__ ImageRenderData ;

/* Variables and functions */

__attribute__((used)) static int
cmp_by_zindex_and_image(const void *a_, const void *b_) {
    const ImageRenderData *a = (const ImageRenderData*)a_, *b = (const ImageRenderData*)b_;
    int ans = a->z_index - b->z_index;
    if (ans == 0) ans = a->image_id - b->image_id;
    return ans;
}