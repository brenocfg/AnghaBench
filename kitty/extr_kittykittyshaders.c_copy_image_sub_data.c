#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  pixel ;
typedef  int /*<<< orphan*/  GLuint ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_ARB_copy_image ; 
 int /*<<< orphan*/  GL_RGBA ; 
 int /*<<< orphan*/  GL_TEXTURE_2D_ARRAY ; 
 int /*<<< orphan*/  GL_UNPACK_ALIGNMENT ; 
 int /*<<< orphan*/  GL_UNSIGNED_BYTE ; 
 int copy_image_warned ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glBindTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glCopyImageSubData (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  glGetTexImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glPixelStorei (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  glTexSubImage3D (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_error (char*) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 

__attribute__((used)) static void
copy_image_sub_data(GLuint src_texture_id, GLuint dest_texture_id, unsigned int width, unsigned int height, unsigned int num_levels) {
    if (!GLAD_GL_ARB_copy_image) {
        // ARB_copy_image not available, do a slow roundtrip copy
        if (!copy_image_warned) {
            copy_image_warned = true;
            log_error("WARNING: Your system's OpenGL implementation does not have glCopyImageSubData, falling back to a slower implementation");
        }
        size_t sz = width * height * num_levels;
        pixel *src = malloc(sz * sizeof(pixel));
        if (src == NULL) { fatal("Out of memory."); }
        glBindTexture(GL_TEXTURE_2D_ARRAY, src_texture_id);
        glGetTexImage(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, GL_UNSIGNED_BYTE, src);
        glBindTexture(GL_TEXTURE_2D_ARRAY, dest_texture_id);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
        glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, 0, width, height, num_levels, GL_RGBA, GL_UNSIGNED_BYTE, src);
        free(src);
    } else {
        glCopyImageSubData(src_texture_id, GL_TEXTURE_2D_ARRAY, 0, 0, 0, 0, dest_texture_id, GL_TEXTURE_2D_ARRAY, 0, 0, 0, 0, width, height, num_levels);
    }
}