#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {void* offline; } ;
struct TYPE_12__ {int client; int source; int major; int minor; int robustness; int profile; int release; void* noerror; void* debug; void* forward; TYPE_3__ nsgl; } ;
struct TYPE_9__ {void* retina; } ;
struct TYPE_11__ {void* focusOnShow; void* centerCursor; void* scaleToMonitor; TYPE_2__ ns; void* visible; void* maximized; void* floating; void* autoIconify; void* focused; void* decorated; void* resizable; } ;
struct TYPE_8__ {int redBits; int greenBits; int blueBits; int alphaBits; int depthBits; int stencilBits; int accumRedBits; int accumGreenBits; int accumBlueBits; int accumAlphaBits; int auxBuffers; int samples; void* sRGB; void* transparent; void* doublebuffer; void* stereo; } ;
struct TYPE_13__ {int refreshRate; TYPE_5__ context; TYPE_4__ window; TYPE_1__ framebuffer; } ;
struct TYPE_14__ {TYPE_6__ hints; } ;

/* Variables and functions */
#define  GLFW_ACCUM_ALPHA_BITS 166 
#define  GLFW_ACCUM_BLUE_BITS 165 
#define  GLFW_ACCUM_GREEN_BITS 164 
#define  GLFW_ACCUM_RED_BITS 163 
#define  GLFW_ALPHA_BITS 162 
#define  GLFW_AUTO_ICONIFY 161 
#define  GLFW_AUX_BUFFERS 160 
#define  GLFW_BLUE_BITS 159 
#define  GLFW_CENTER_CURSOR 158 
#define  GLFW_CLIENT_API 157 
#define  GLFW_COCOA_GRAPHICS_SWITCHING 156 
#define  GLFW_COCOA_RETINA_FRAMEBUFFER 155 
#define  GLFW_CONTEXT_CREATION_API 154 
#define  GLFW_CONTEXT_NO_ERROR 153 
#define  GLFW_CONTEXT_RELEASE_BEHAVIOR 152 
#define  GLFW_CONTEXT_ROBUSTNESS 151 
#define  GLFW_CONTEXT_VERSION_MAJOR 150 
#define  GLFW_CONTEXT_VERSION_MINOR 149 
#define  GLFW_DECORATED 148 
#define  GLFW_DEPTH_BITS 147 
#define  GLFW_DOUBLEBUFFER 146 
 void* GLFW_FALSE ; 
#define  GLFW_FLOATING 145 
#define  GLFW_FOCUSED 144 
#define  GLFW_FOCUS_ON_SHOW 143 
#define  GLFW_GREEN_BITS 142 
 int /*<<< orphan*/  GLFW_INVALID_ENUM ; 
#define  GLFW_MAXIMIZED 141 
#define  GLFW_OPENGL_DEBUG_CONTEXT 140 
#define  GLFW_OPENGL_FORWARD_COMPAT 139 
#define  GLFW_OPENGL_PROFILE 138 
#define  GLFW_RED_BITS 137 
#define  GLFW_REFRESH_RATE 136 
#define  GLFW_RESIZABLE 135 
#define  GLFW_SAMPLES 134 
#define  GLFW_SCALE_TO_MONITOR 133 
#define  GLFW_SRGB_CAPABLE 132 
#define  GLFW_STENCIL_BITS 131 
#define  GLFW_STEREO 130 
#define  GLFW_TRANSPARENT_FRAMEBUFFER 129 
 void* GLFW_TRUE ; 
#define  GLFW_VISIBLE 128 
 int /*<<< orphan*/  _GLFW_REQUIRE_INIT () ; 
 TYPE_7__ _glfw ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*,int) ; 

void glfwWindowHint(int hint, int value)
{
    _GLFW_REQUIRE_INIT();

    switch (hint)
    {
        case GLFW_RED_BITS:
            _glfw.hints.framebuffer.redBits = value;
            return;
        case GLFW_GREEN_BITS:
            _glfw.hints.framebuffer.greenBits = value;
            return;
        case GLFW_BLUE_BITS:
            _glfw.hints.framebuffer.blueBits = value;
            return;
        case GLFW_ALPHA_BITS:
            _glfw.hints.framebuffer.alphaBits = value;
            return;
        case GLFW_DEPTH_BITS:
            _glfw.hints.framebuffer.depthBits = value;
            return;
        case GLFW_STENCIL_BITS:
            _glfw.hints.framebuffer.stencilBits = value;
            return;
        case GLFW_ACCUM_RED_BITS:
            _glfw.hints.framebuffer.accumRedBits = value;
            return;
        case GLFW_ACCUM_GREEN_BITS:
            _glfw.hints.framebuffer.accumGreenBits = value;
            return;
        case GLFW_ACCUM_BLUE_BITS:
            _glfw.hints.framebuffer.accumBlueBits = value;
            return;
        case GLFW_ACCUM_ALPHA_BITS:
            _glfw.hints.framebuffer.accumAlphaBits = value;
            return;
        case GLFW_AUX_BUFFERS:
            _glfw.hints.framebuffer.auxBuffers = value;
            return;
        case GLFW_STEREO:
            _glfw.hints.framebuffer.stereo = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_DOUBLEBUFFER:
            _glfw.hints.framebuffer.doublebuffer = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_TRANSPARENT_FRAMEBUFFER:
            _glfw.hints.framebuffer.transparent = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_SAMPLES:
            _glfw.hints.framebuffer.samples = value;
            return;
        case GLFW_SRGB_CAPABLE:
            _glfw.hints.framebuffer.sRGB = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_RESIZABLE:
            _glfw.hints.window.resizable = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_DECORATED:
            _glfw.hints.window.decorated = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_FOCUSED:
            _glfw.hints.window.focused = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_AUTO_ICONIFY:
            _glfw.hints.window.autoIconify = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_FLOATING:
            _glfw.hints.window.floating = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_MAXIMIZED:
            _glfw.hints.window.maximized = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_VISIBLE:
            _glfw.hints.window.visible = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_COCOA_RETINA_FRAMEBUFFER:
            _glfw.hints.window.ns.retina = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_COCOA_GRAPHICS_SWITCHING:
            _glfw.hints.context.nsgl.offline = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_SCALE_TO_MONITOR:
            _glfw.hints.window.scaleToMonitor = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_CENTER_CURSOR:
            _glfw.hints.window.centerCursor = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_FOCUS_ON_SHOW:
            _glfw.hints.window.focusOnShow = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_CLIENT_API:
            _glfw.hints.context.client = value;
            return;
        case GLFW_CONTEXT_CREATION_API:
            _glfw.hints.context.source = value;
            return;
        case GLFW_CONTEXT_VERSION_MAJOR:
            _glfw.hints.context.major = value;
            return;
        case GLFW_CONTEXT_VERSION_MINOR:
            _glfw.hints.context.minor = value;
            return;
        case GLFW_CONTEXT_ROBUSTNESS:
            _glfw.hints.context.robustness = value;
            return;
        case GLFW_OPENGL_FORWARD_COMPAT:
            _glfw.hints.context.forward = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_OPENGL_DEBUG_CONTEXT:
            _glfw.hints.context.debug = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_CONTEXT_NO_ERROR:
            _glfw.hints.context.noerror = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_OPENGL_PROFILE:
            _glfw.hints.context.profile = value;
            return;
        case GLFW_CONTEXT_RELEASE_BEHAVIOR:
            _glfw.hints.context.release = value;
            return;
        case GLFW_REFRESH_RATE:
            _glfw.hints.refreshRate = value;
            return;
    }

    _glfwInputError(GLFW_INVALID_ENUM, "Invalid window hint 0x%08X", hint);
}