#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int ynum; scalar_t__ z; scalar_t__ y; scalar_t__ x; void* max_y; void* xnum; } ;
typedef  TYPE_1__ GPUSpriteTracker ;

/* Variables and functions */
 int /*<<< orphan*/  MAX (int,unsigned int) ; 
 void* MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT16_MAX ; 
 unsigned int max_texture_size ; 

__attribute__((used)) static void
sprite_tracker_set_layout(GPUSpriteTracker *sprite_tracker, unsigned int cell_width, unsigned int cell_height) {
    sprite_tracker->xnum = MIN(MAX(1, max_texture_size / cell_width), UINT16_MAX);
    sprite_tracker->max_y = MIN(MAX(1, max_texture_size / cell_height), UINT16_MAX);
    sprite_tracker->ynum = 1;
    sprite_tracker->x = 0; sprite_tracker->y = 0; sprite_tracker->z = 0;
}