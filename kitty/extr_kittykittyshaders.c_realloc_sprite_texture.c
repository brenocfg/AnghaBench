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
struct TYPE_5__ {unsigned int cell_width; unsigned int cell_height; unsigned int last_ynum; unsigned int last_num_of_layers; scalar_t__ texture_id; } ;
typedef  TYPE_1__ SpriteMap ;
typedef  scalar_t__ GLuint ;
typedef  TYPE_2__* FONTS_DATA_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  GL_CLAMP_TO_EDGE ; 
 int /*<<< orphan*/  GL_NEAREST ; 
 int /*<<< orphan*/  GL_RGBA8 ; 
 int /*<<< orphan*/  GL_TEXTURE_2D_ARRAY ; 
 int /*<<< orphan*/  GL_TEXTURE_MAG_FILTER ; 
 int /*<<< orphan*/  GL_TEXTURE_MIN_FILTER ; 
 int /*<<< orphan*/  GL_TEXTURE_WRAP_S ; 
 int /*<<< orphan*/  GL_TEXTURE_WRAP_T ; 
 unsigned int MAX (int,unsigned int) ; 
 int /*<<< orphan*/  copy_image_sub_data (scalar_t__,scalar_t__,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  glBindTexture (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  glDeleteTextures (int,scalar_t__*) ; 
 int /*<<< orphan*/  glGenTextures (int,scalar_t__*) ; 
 int /*<<< orphan*/  glTexParameteri (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glTexStorage3D (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  sprite_tracker_current_layout (TYPE_2__*,unsigned int*,unsigned int*,unsigned int*) ; 

__attribute__((used)) static void
realloc_sprite_texture(FONTS_DATA_HANDLE fg) {
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D_ARRAY, tex);
    // We use GL_NEAREST otherwise glyphs that touch the edge of the cell
    // often show a border between cells
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    unsigned int xnum, ynum, z, znum, width, height, src_ynum;
    sprite_tracker_current_layout(fg, &xnum, &ynum, &z);
    znum = z + 1;
    SpriteMap *sprite_map = (SpriteMap*)fg->sprite_map;
    width = xnum * sprite_map->cell_width; height = ynum * sprite_map->cell_height;
    glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA8, width, height, znum);
    if (sprite_map->texture_id) {
        // need to re-alloc
        src_ynum = MAX(1, sprite_map->last_ynum);
        copy_image_sub_data(sprite_map->texture_id, tex, width, src_ynum * sprite_map->cell_height, sprite_map->last_num_of_layers);
        glDeleteTextures(1, &sprite_map->texture_id);
    }
    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
    sprite_map->last_num_of_layers = znum;
    sprite_map->last_ynum = ynum;
    sprite_map->texture_id = tex;
}