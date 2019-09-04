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
struct TYPE_3__ {scalar_t__ texture_id; } ;
typedef  TYPE_1__ SpriteMap ;
typedef  int /*<<< orphan*/ * SPRITE_MAP_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  free_texture (scalar_t__*) ; 

SPRITE_MAP_HANDLE
free_sprite_map(SPRITE_MAP_HANDLE sm) {
    SpriteMap *sprite_map = (SpriteMap*)sm;
    if (sprite_map) {
        if (sprite_map->texture_id) free_texture(&sprite_map->texture_id);
        free(sprite_map);
    }
    return NULL;
}