#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_16__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  attribs ;
struct TYPE_20__ {int /*<<< orphan*/  dc; } ;
struct TYPE_21__ {TYPE_2__ wgl; } ;
struct TYPE_22__ {TYPE_3__ context; } ;
typedef  TYPE_4__ _GLFWwindow ;
struct TYPE_23__ {int handle; void* doublebuffer; void* stereo; scalar_t__ auxBuffers; scalar_t__ accumAlphaBits; scalar_t__ accumBlueBits; scalar_t__ accumGreenBits; scalar_t__ accumRedBits; scalar_t__ stencilBits; scalar_t__ depthBits; scalar_t__ alphaBits; scalar_t__ blueBits; scalar_t__ greenBits; scalar_t__ redBits; void* sRGB; scalar_t__ samples; } ;
typedef  TYPE_5__ _GLFWfbconfig ;
struct TYPE_24__ {scalar_t__ client; } ;
typedef  TYPE_6__ _GLFWctxconfig ;
struct TYPE_25__ {int dwFlags; scalar_t__ iPixelType; scalar_t__ cAuxBuffers; scalar_t__ cAccumAlphaBits; scalar_t__ cAccumBlueBits; scalar_t__ cAccumGreenBits; scalar_t__ cAccumRedBits; scalar_t__ cStencilBits; scalar_t__ cDepthBits; scalar_t__ cAlphaBits; scalar_t__ cBlueBits; scalar_t__ cGreenBits; scalar_t__ cRedBits; } ;
struct TYPE_19__ {scalar_t__ EXT_colorspace; scalar_t__ EXT_framebuffer_sRGB; scalar_t__ ARB_framebuffer_sRGB; scalar_t__ ARB_multisample; scalar_t__ ARB_pixel_format; } ;
struct TYPE_18__ {TYPE_1__ wgl; } ;
typedef  TYPE_7__ PIXELFORMATDESCRIPTOR ;

/* Variables and functions */
 int DescribePixelFormat (int /*<<< orphan*/ ,int,int,TYPE_7__*) ; 
 int /*<<< orphan*/  GLFW_API_UNAVAILABLE ; 
 int /*<<< orphan*/  GLFW_FORMAT_UNAVAILABLE ; 
 scalar_t__ GLFW_OPENGL_API ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 void* GLFW_TRUE ; 
 int PFD_DOUBLEBUFFER ; 
 int PFD_DRAW_TO_WINDOW ; 
 int PFD_GENERIC_ACCELERATED ; 
 int PFD_GENERIC_FORMAT ; 
 int PFD_STEREO ; 
 int PFD_SUPPORT_OPENGL ; 
 scalar_t__ PFD_TYPE_RGBA ; 
 int /*<<< orphan*/  WGL_ACCELERATION_ARB ; 
 int /*<<< orphan*/  WGL_ACCUM_ALPHA_BITS_ARB ; 
 int /*<<< orphan*/  WGL_ACCUM_BITS_ARB ; 
 int /*<<< orphan*/  WGL_ACCUM_BLUE_BITS_ARB ; 
 int /*<<< orphan*/  WGL_ACCUM_GREEN_BITS_ARB ; 
 int /*<<< orphan*/  WGL_ACCUM_RED_BITS_ARB ; 
 int /*<<< orphan*/  WGL_ALPHA_BITS_ARB ; 
 int /*<<< orphan*/  WGL_ALPHA_SHIFT_ARB ; 
 int /*<<< orphan*/  WGL_AUX_BUFFERS_ARB ; 
 int /*<<< orphan*/  WGL_BLUE_BITS_ARB ; 
 int /*<<< orphan*/  WGL_BLUE_SHIFT_ARB ; 
 int /*<<< orphan*/  WGL_COLORSPACE_EXT ; 
 scalar_t__ WGL_COLORSPACE_SRGB_EXT ; 
 int /*<<< orphan*/  WGL_DEPTH_BITS_ARB ; 
 int /*<<< orphan*/  WGL_DOUBLE_BUFFER_ARB ; 
 int /*<<< orphan*/  WGL_DRAW_TO_WINDOW_ARB ; 
 int /*<<< orphan*/  WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB ; 
 int /*<<< orphan*/  WGL_GREEN_BITS_ARB ; 
 int /*<<< orphan*/  WGL_GREEN_SHIFT_ARB ; 
 scalar_t__ WGL_NO_ACCELERATION_ARB ; 
 int WGL_NUMBER_PIXEL_FORMATS_ARB ; 
 int /*<<< orphan*/  WGL_PIXEL_TYPE_ARB ; 
 int /*<<< orphan*/  WGL_RED_BITS_ARB ; 
 int /*<<< orphan*/  WGL_RED_SHIFT_ARB ; 
 int /*<<< orphan*/  WGL_SAMPLES_ARB ; 
 int /*<<< orphan*/  WGL_STENCIL_BITS_ARB ; 
 int /*<<< orphan*/  WGL_STEREO_ARB ; 
 int /*<<< orphan*/  WGL_SUPPORT_OPENGL_ARB ; 
 scalar_t__ WGL_TYPE_RGBA_ARB ; 
 TYPE_16__ _glfw ; 
 TYPE_5__* _glfwChooseFBConfig (TYPE_5__ const*,TYPE_5__*,int) ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _glfwInputErrorWin32 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  addAttrib (int /*<<< orphan*/ ) ; 
 TYPE_5__* calloc (int,int) ; 
 scalar_t__ findAttribValue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_5__*) ; 
 int /*<<< orphan*/  wglGetPixelFormatAttribivARB (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int const*,int*) ; 

__attribute__((used)) static int choosePixelFormat(_GLFWwindow* window,
                             const _GLFWctxconfig* ctxconfig,
                             const _GLFWfbconfig* fbconfig)
{
    _GLFWfbconfig* usableConfigs;
    const _GLFWfbconfig* closest;
    int i, pixelFormat, nativeCount, usableCount = 0, attribCount = 0;
    int attribs[40];
    int values[sizeof(attribs) / sizeof(attribs[0])];

    if (_glfw.wgl.ARB_pixel_format)
    {
        const int attrib = WGL_NUMBER_PIXEL_FORMATS_ARB;

        if (!wglGetPixelFormatAttribivARB(window->context.wgl.dc,
                                          1, 0, 1, &attrib, &nativeCount))
        {
            _glfwInputErrorWin32(GLFW_PLATFORM_ERROR,
                                 "WGL: Failed to retrieve pixel format attribute");
            return 0;
        }

        addAttrib(WGL_SUPPORT_OPENGL_ARB);
        addAttrib(WGL_DRAW_TO_WINDOW_ARB);
        addAttrib(WGL_PIXEL_TYPE_ARB);
        addAttrib(WGL_ACCELERATION_ARB);
        addAttrib(WGL_RED_BITS_ARB);
        addAttrib(WGL_RED_SHIFT_ARB);
        addAttrib(WGL_GREEN_BITS_ARB);
        addAttrib(WGL_GREEN_SHIFT_ARB);
        addAttrib(WGL_BLUE_BITS_ARB);
        addAttrib(WGL_BLUE_SHIFT_ARB);
        addAttrib(WGL_ALPHA_BITS_ARB);
        addAttrib(WGL_ALPHA_SHIFT_ARB);
        addAttrib(WGL_DEPTH_BITS_ARB);
        addAttrib(WGL_STENCIL_BITS_ARB);
        addAttrib(WGL_ACCUM_BITS_ARB);
        addAttrib(WGL_ACCUM_RED_BITS_ARB);
        addAttrib(WGL_ACCUM_GREEN_BITS_ARB);
        addAttrib(WGL_ACCUM_BLUE_BITS_ARB);
        addAttrib(WGL_ACCUM_ALPHA_BITS_ARB);
        addAttrib(WGL_AUX_BUFFERS_ARB);
        addAttrib(WGL_STEREO_ARB);
        addAttrib(WGL_DOUBLE_BUFFER_ARB);

        if (_glfw.wgl.ARB_multisample)
            addAttrib(WGL_SAMPLES_ARB);

        if (ctxconfig->client == GLFW_OPENGL_API)
        {
            if (_glfw.wgl.ARB_framebuffer_sRGB || _glfw.wgl.EXT_framebuffer_sRGB)
                addAttrib(WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB);
        }
        else
        {
            if (_glfw.wgl.EXT_colorspace)
                addAttrib(WGL_COLORSPACE_EXT);
        }
    }
    else
    {
        nativeCount = DescribePixelFormat(window->context.wgl.dc,
                                          1,
                                          sizeof(PIXELFORMATDESCRIPTOR),
                                          NULL);
    }

    usableConfigs = calloc(nativeCount, sizeof(_GLFWfbconfig));

    for (i = 0;  i < nativeCount;  i++)
    {
        _GLFWfbconfig* u = usableConfigs + usableCount;
        pixelFormat = i + 1;

        if (_glfw.wgl.ARB_pixel_format)
        {
            // Get pixel format attributes through "modern" extension

            if (!wglGetPixelFormatAttribivARB(window->context.wgl.dc,
                                              pixelFormat, 0,
                                              attribCount,
                                              attribs, values))
            {
                _glfwInputErrorWin32(GLFW_PLATFORM_ERROR,
                                    "WGL: Failed to retrieve pixel format attributes");

                free(usableConfigs);
                return 0;
            }

            if (!findAttribValue(WGL_SUPPORT_OPENGL_ARB) ||
                !findAttribValue(WGL_DRAW_TO_WINDOW_ARB))
            {
                continue;
            }

            if (findAttribValue(WGL_PIXEL_TYPE_ARB) != WGL_TYPE_RGBA_ARB)
                continue;

            if (findAttribValue(WGL_ACCELERATION_ARB) == WGL_NO_ACCELERATION_ARB)
                continue;

            u->redBits = findAttribValue(WGL_RED_BITS_ARB);
            u->greenBits = findAttribValue(WGL_GREEN_BITS_ARB);
            u->blueBits = findAttribValue(WGL_BLUE_BITS_ARB);
            u->alphaBits = findAttribValue(WGL_ALPHA_BITS_ARB);

            u->depthBits = findAttribValue(WGL_DEPTH_BITS_ARB);
            u->stencilBits = findAttribValue(WGL_STENCIL_BITS_ARB);

            u->accumRedBits = findAttribValue(WGL_ACCUM_RED_BITS_ARB);
            u->accumGreenBits = findAttribValue(WGL_ACCUM_GREEN_BITS_ARB);
            u->accumBlueBits = findAttribValue(WGL_ACCUM_BLUE_BITS_ARB);
            u->accumAlphaBits = findAttribValue(WGL_ACCUM_ALPHA_BITS_ARB);

            u->auxBuffers = findAttribValue(WGL_AUX_BUFFERS_ARB);

            if (findAttribValue(WGL_STEREO_ARB))
                u->stereo = GLFW_TRUE;
            if (findAttribValue(WGL_DOUBLE_BUFFER_ARB))
                u->doublebuffer = GLFW_TRUE;

            if (_glfw.wgl.ARB_multisample)
                u->samples = findAttribValue(WGL_SAMPLES_ARB);

            if (ctxconfig->client == GLFW_OPENGL_API)
            {
                if (_glfw.wgl.ARB_framebuffer_sRGB ||
                    _glfw.wgl.EXT_framebuffer_sRGB)
                {
                    if (findAttribValue(WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB))
                        u->sRGB = GLFW_TRUE;
                }
            }
            else
            {
                if (_glfw.wgl.EXT_colorspace)
                {
                    if (findAttribValue(WGL_COLORSPACE_EXT) == WGL_COLORSPACE_SRGB_EXT)
                        u->sRGB = GLFW_TRUE;
                }
            }
        }
        else
        {
            // Get pixel format attributes through legacy PFDs

            PIXELFORMATDESCRIPTOR pfd;

            if (!DescribePixelFormat(window->context.wgl.dc,
                                     pixelFormat,
                                     sizeof(PIXELFORMATDESCRIPTOR),
                                     &pfd))
            {
                _glfwInputErrorWin32(GLFW_PLATFORM_ERROR,
                                    "WGL: Failed to describe pixel format");

                free(usableConfigs);
                return 0;
            }

            if (!(pfd.dwFlags & PFD_DRAW_TO_WINDOW) ||
                !(pfd.dwFlags & PFD_SUPPORT_OPENGL))
            {
                continue;
            }

            if (!(pfd.dwFlags & PFD_GENERIC_ACCELERATED) &&
                (pfd.dwFlags & PFD_GENERIC_FORMAT))
            {
                continue;
            }

            if (pfd.iPixelType != PFD_TYPE_RGBA)
                continue;

            u->redBits = pfd.cRedBits;
            u->greenBits = pfd.cGreenBits;
            u->blueBits = pfd.cBlueBits;
            u->alphaBits = pfd.cAlphaBits;

            u->depthBits = pfd.cDepthBits;
            u->stencilBits = pfd.cStencilBits;

            u->accumRedBits = pfd.cAccumRedBits;
            u->accumGreenBits = pfd.cAccumGreenBits;
            u->accumBlueBits = pfd.cAccumBlueBits;
            u->accumAlphaBits = pfd.cAccumAlphaBits;

            u->auxBuffers = pfd.cAuxBuffers;

            if (pfd.dwFlags & PFD_STEREO)
                u->stereo = GLFW_TRUE;
            if (pfd.dwFlags & PFD_DOUBLEBUFFER)
                u->doublebuffer = GLFW_TRUE;
        }

        u->handle = pixelFormat;
        usableCount++;
    }

    if (!usableCount)
    {
        _glfwInputError(GLFW_API_UNAVAILABLE,
                        "WGL: The driver does not appear to support OpenGL");

        free(usableConfigs);
        return 0;
    }

    closest = _glfwChooseFBConfig(fbconfig, usableConfigs, usableCount);
    if (!closest)
    {
        _glfwInputError(GLFW_FORMAT_UNAVAILABLE,
                        "WGL: Failed to find a suitable pixel format");

        free(usableConfigs);
        return 0;
    }

    pixelFormat = (int) closest->handle;
    free(usableConfigs);

    return pixelFormat;
}