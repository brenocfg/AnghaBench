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
struct TYPE_6__ {int sprite_z; int /*<<< orphan*/  sprite_y; int /*<<< orphan*/  sprite_x; } ;
struct TYPE_5__ {int z; scalar_t__ colored; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ SpritePosition ;
typedef  TYPE_2__ GPUCell ;

/* Variables and functions */

__attribute__((used)) static inline void
set_cell_sprite(GPUCell *cell, SpritePosition *sp) {
    cell->sprite_x = sp->x; cell->sprite_y = sp->y; cell->sprite_z = sp->z;
    if (sp->colored) cell->sprite_z |= 0x4000;
}