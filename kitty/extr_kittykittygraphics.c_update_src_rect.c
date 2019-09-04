#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ height; scalar_t__ width; } ;
struct TYPE_6__ {float left; float right; float top; float bottom; } ;
struct TYPE_7__ {scalar_t__ src_height; scalar_t__ src_y; TYPE_1__ src_rect; scalar_t__ src_width; scalar_t__ src_x; } ;
typedef  TYPE_2__ ImageRef ;
typedef  TYPE_3__ Image ;

/* Variables and functions */

__attribute__((used)) static inline void
update_src_rect(ImageRef *ref, Image *img) {
    // The src rect in OpenGL co-ords [0, 1] with origin at top-left corner of image
    ref->src_rect.left = (float)ref->src_x / (float)img->width;
    ref->src_rect.right = (float)(ref->src_x + ref->src_width) / (float)img->width;
    ref->src_rect.top = (float)ref->src_y / (float)img->height;
    ref->src_rect.bottom = (float)(ref->src_y + ref->src_height) / (float)img->height;
}