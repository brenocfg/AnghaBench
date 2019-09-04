#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int cell_width; unsigned int cell_height; void* max_array_texture_layers; void* max_texture_size; } ;
typedef  TYPE_1__ SpriteMap ;
typedef  int /*<<< orphan*/  SPRITE_MAP_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  GL_MAX_ARRAY_TEXTURE_LAYERS ; 
 int /*<<< orphan*/  GL_MAX_TEXTURE_SIZE ; 
 TYPE_1__ NEW_SPRITE_MAP ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  glGetIntegerv (int /*<<< orphan*/ ,void**) ; 
 void* max_array_texture_layers ; 
 void* max_texture_size ; 
 int /*<<< orphan*/  sprite_tracker_set_limits (void*,void*) ; 

SPRITE_MAP_HANDLE
alloc_sprite_map(unsigned int cell_width, unsigned int cell_height) {
    if (!max_texture_size) {
        glGetIntegerv(GL_MAX_TEXTURE_SIZE, &(max_texture_size));
        glGetIntegerv(GL_MAX_ARRAY_TEXTURE_LAYERS, &(max_array_texture_layers));
#ifdef __APPLE__
        // Since on Apple we could have multiple GPUs, with different capabilities,
        // upper bound the values according to the data from https://developer.apple.com/graphicsimaging/opengl/capabilities/
        max_texture_size = MIN(8192, max_texture_size);
        max_array_texture_layers = MIN(512, max_array_texture_layers);
#endif
        sprite_tracker_set_limits(max_texture_size, max_array_texture_layers);
    }
    SpriteMap *ans = calloc(1, sizeof(SpriteMap));
    if (ans) {
        *ans = NEW_SPRITE_MAP;
        ans->max_texture_size = max_texture_size;
        ans->max_array_texture_layers = max_array_texture_layers;
        ans->cell_width = cell_width; ans->cell_height = cell_height;
    }
    return (SPRITE_MAP_HANDLE)ans;
}