#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  top; int /*<<< orphan*/  left; int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; } ;
struct TYPE_8__ {int /*<<< orphan*/  top; int /*<<< orphan*/  left; int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; } ;
struct TYPE_10__ {TYPE_1__ src_rect; } ;
struct TYPE_9__ {int /*<<< orphan*/ * vertices; } ;
typedef  TYPE_2__ ImageRenderData ;
typedef  TYPE_3__ ImageRef ;
typedef  TYPE_4__ ImageRect ;

/* Variables and functions */

__attribute__((used)) static inline void
set_vertex_data(ImageRenderData *rd, const ImageRef *ref, const ImageRect *dest_rect) {
#define R(n, a, b) rd->vertices[n*4] = ref->src_rect.a; rd->vertices[n*4 + 1] = ref->src_rect.b; rd->vertices[n*4 + 2] = dest_rect->a; rd->vertices[n*4 + 3] = dest_rect->b;
        R(0, right, top); R(1, right, bottom); R(2, left, bottom); R(3, left, top);
#undef R
}