#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int major; int minor; } ;
struct TYPE_3__ {scalar_t__ debug_gl; } ;
typedef  int /*<<< orphan*/  GLADloadproc ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_ARB_texture_storage ; 
 TYPE_2__ GLVersion ; 
 int /*<<< orphan*/  GL_VERSION ; 
 int OPENGL_REQUIRED_VERSION_MAJOR ; 
 scalar_t__ OPENGL_REQUIRED_VERSION_MINOR ; 
 int /*<<< orphan*/  check_for_gl_error ; 
 int /*<<< orphan*/  fatal (char*,...) ; 
 char* glGetString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glad_set_post_callback (int /*<<< orphan*/ ) ; 
 scalar_t__ glfwGetProcAddress ; 
 TYPE_1__ global_state ; 
 int /*<<< orphan*/  init_glad (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,char*,int,int) ; 

void
gl_init() {
    static bool glad_loaded = false;
    if (!glad_loaded) {
        if (!init_glad((GLADloadproc) glfwGetProcAddress, global_state.debug_gl)) {
            fatal("Loading the OpenGL library failed");
        }
        glad_set_post_callback(check_for_gl_error);
#define ARB_TEST(name) \
        if (!GLAD_GL_ARB_##name) { \
            fatal("The OpenGL driver on this system is missing the required extension: ARB_%s", #name); \
        }
        ARB_TEST(texture_storage);
#undef ARB_TEST
        glad_loaded = true;
        if (global_state.debug_gl) printf("GL version string: '%s' Detected version: %d.%d\n", glGetString(GL_VERSION), GLVersion.major, GLVersion.minor);
        if (GLVersion.major < OPENGL_REQUIRED_VERSION_MAJOR || (GLVersion.major == OPENGL_REQUIRED_VERSION_MAJOR && GLVersion.minor < OPENGL_REQUIRED_VERSION_MINOR)) {
            fatal("OpenGL version is %d.%d, version >= 3.3 required for kitty", GLVersion.major, GLVersion.minor);
        }
    }
}