#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_6__ {size_t image_count; TYPE_1__* images; } ;
struct TYPE_5__ {scalar_t__ client_id; } ;
typedef  TYPE_1__ Image ;
typedef  TYPE_2__ GraphicsManager ;

/* Variables and functions */

__attribute__((used)) static inline Image*
img_by_client_id(GraphicsManager *self, uint32_t id) {
    for (size_t i = 0; i < self->image_count; i++) {
        if (self->images[i].client_id == id) return self->images + i;
    }
    return NULL;
}