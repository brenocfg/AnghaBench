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
typedef  void* sprite_index ;
struct TYPE_3__ {void* sprite_z; void* sprite_y; void* sprite_x; } ;
typedef  TYPE_1__ GPUCell ;

/* Variables and functions */

__attribute__((used)) static inline void
set_sprite(GPUCell *cell, sprite_index x, sprite_index y, sprite_index z) {
    cell->sprite_x = x; cell->sprite_y = y; cell->sprite_z = z;
}