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
struct TYPE_6__ {scalar_t__ sprite_map; } ;
struct TYPE_5__ {int /*<<< orphan*/  texture_id; } ;
typedef  TYPE_1__ SpriteMap ;
typedef  TYPE_2__* FONTS_DATA_HANDLE ;

/* Variables and functions */
 scalar_t__ GL_TEXTURE0 ; 
 int /*<<< orphan*/  GL_TEXTURE_2D_ARRAY ; 
 scalar_t__ SPRITE_MAP_UNIT ; 
 int /*<<< orphan*/  glActiveTexture (scalar_t__) ; 
 int /*<<< orphan*/  glBindTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  realloc_sprite_texture (TYPE_2__*) ; 

__attribute__((used)) static inline void
ensure_sprite_map(FONTS_DATA_HANDLE fg) {
    SpriteMap *sprite_map = (SpriteMap*)fg->sprite_map;
    if (!sprite_map->texture_id) realloc_sprite_texture(fg);
    // We have to rebind since we don't know if the texture was ever bound
    // in the context of the current OSWindow
    glActiveTexture(GL_TEXTURE0 + SPRITE_MAP_UNIT);
    glBindTexture(GL_TEXTURE_2D_ARRAY, sprite_map->texture_id);
}