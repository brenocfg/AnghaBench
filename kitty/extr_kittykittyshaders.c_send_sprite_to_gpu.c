#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pixel ;
struct TYPE_7__ {scalar_t__ sprite_map; } ;
struct TYPE_6__ {int last_num_of_layers; int last_ynum; unsigned int cell_width; unsigned int cell_height; int /*<<< orphan*/  texture_id; } ;
typedef  TYPE_1__ SpriteMap ;
typedef  TYPE_2__* FONTS_DATA_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  GL_RGBA ; 
 int /*<<< orphan*/  GL_TEXTURE_2D_ARRAY ; 
 int /*<<< orphan*/  GL_UNPACK_ALIGNMENT ; 
 int /*<<< orphan*/  GL_UNSIGNED_INT_8_8_8_8 ; 
 int /*<<< orphan*/  glBindTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glPixelStorei (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  glTexSubImage3D (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  realloc_sprite_texture (TYPE_2__*) ; 
 int /*<<< orphan*/  sprite_tracker_current_layout (TYPE_2__*,unsigned int*,unsigned int*,unsigned int*) ; 

void
send_sprite_to_gpu(FONTS_DATA_HANDLE fg, unsigned int x, unsigned int y, unsigned int z, pixel *buf) {
    SpriteMap *sprite_map = (SpriteMap*)fg->sprite_map;
    unsigned int xnum, ynum, znum;
    sprite_tracker_current_layout(fg, &xnum, &ynum, &znum);
    if ((int)znum >= sprite_map->last_num_of_layers || (znum == 0 && (int)ynum > sprite_map->last_ynum)) realloc_sprite_texture(fg);
    glBindTexture(GL_TEXTURE_2D_ARRAY, sprite_map->texture_id);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    x *= sprite_map->cell_width; y *= sprite_map->cell_height;
    glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, x, y, z, sprite_map->cell_width, sprite_map->cell_height, 1, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, buf);
}