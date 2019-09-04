#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* retina; } ;
struct TYPE_7__ {int major; int redBits; int greenBits; int blueBits; int alphaBits; int depthBits; int stencilBits; TYPE_1__ ns; void* doublebuffer; void* focusOnShow; void* centerCursor; void* autoIconify; void* focused; void* decorated; void* visible; void* resizable; scalar_t__ minor; int /*<<< orphan*/  source; int /*<<< orphan*/  client; } ;
struct TYPE_6__ {TYPE_3__ window; int /*<<< orphan*/  refreshRate; TYPE_3__ framebuffer; TYPE_3__ context; } ;
struct TYPE_8__ {TYPE_2__ hints; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_DONT_CARE ; 
 int /*<<< orphan*/  GLFW_NATIVE_CONTEXT_API ; 
 int /*<<< orphan*/  GLFW_OPENGL_API ; 
 void* GLFW_TRUE ; 
 int /*<<< orphan*/  _GLFW_REQUIRE_INIT () ; 
 TYPE_4__ _glfw ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

void glfwDefaultWindowHints(void)
{
    _GLFW_REQUIRE_INIT();

    // The default is OpenGL with minimum version 1.0
    memset(&_glfw.hints.context, 0, sizeof(_glfw.hints.context));
    _glfw.hints.context.client = GLFW_OPENGL_API;
    _glfw.hints.context.source = GLFW_NATIVE_CONTEXT_API;
    _glfw.hints.context.major  = 1;
    _glfw.hints.context.minor  = 0;

    // The default is a focused, visible, resizable window with decorations
    memset(&_glfw.hints.window, 0, sizeof(_glfw.hints.window));
    _glfw.hints.window.resizable    = GLFW_TRUE;
    _glfw.hints.window.visible      = GLFW_TRUE;
    _glfw.hints.window.decorated    = GLFW_TRUE;
    _glfw.hints.window.focused      = GLFW_TRUE;
    _glfw.hints.window.autoIconify  = GLFW_TRUE;
    _glfw.hints.window.centerCursor = GLFW_TRUE;
    _glfw.hints.window.focusOnShow  = GLFW_TRUE;

    // The default is 24 bits of color, 24 bits of depth and 8 bits of stencil,
    // double buffered
    memset(&_glfw.hints.framebuffer, 0, sizeof(_glfw.hints.framebuffer));
    _glfw.hints.framebuffer.redBits      = 8;
    _glfw.hints.framebuffer.greenBits    = 8;
    _glfw.hints.framebuffer.blueBits     = 8;
    _glfw.hints.framebuffer.alphaBits    = 8;
    _glfw.hints.framebuffer.depthBits    = 24;
    _glfw.hints.framebuffer.stencilBits  = 8;
    _glfw.hints.framebuffer.doublebuffer = GLFW_TRUE;

    // The default is to select the highest available refresh rate
    _glfw.hints.refreshRate = GLFW_DONT_CARE;

    // The default is to use full Retina resolution framebuffers
    _glfw.hints.window.ns.retina = GLFW_TRUE;
}