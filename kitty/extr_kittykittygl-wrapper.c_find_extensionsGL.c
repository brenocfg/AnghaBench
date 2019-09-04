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

/* Variables and functions */
 void* GLAD_GL_ARB_copy_image ; 
 void* GLAD_GL_ARB_multisample ; 
 void* GLAD_GL_ARB_robustness ; 
 void* GLAD_GL_ARB_texture_storage ; 
 void* GLAD_GL_KHR_debug ; 
 int /*<<< orphan*/  free_exts () ; 
 int /*<<< orphan*/  get_exts () ; 
 void* has_ext (char*) ; 

__attribute__((used)) static int find_extensionsGL(void) {
	if (!get_exts()) return 0;
	GLAD_GL_ARB_copy_image = has_ext("GL_ARB_copy_image");
	GLAD_GL_ARB_multisample = has_ext("GL_ARB_multisample");
	GLAD_GL_ARB_robustness = has_ext("GL_ARB_robustness");
	GLAD_GL_ARB_texture_storage = has_ext("GL_ARB_texture_storage");
	GLAD_GL_KHR_debug = has_ext("GL_KHR_debug");
	free_exts();
	return 1;
}