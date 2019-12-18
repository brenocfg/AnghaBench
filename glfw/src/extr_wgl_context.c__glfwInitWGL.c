#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pfd ;
struct TYPE_9__ {void* ARB_context_flush_control; void* ARB_pixel_format; void* EXT_colorspace; void* EXT_swap_control; void* ARB_create_context_no_error; void* ARB_create_context_robustness; void* EXT_create_context_es2_profile; void* ARB_create_context_profile; void* ARB_create_context; void* EXT_framebuffer_sRGB; void* ARB_framebuffer_sRGB; void* ARB_multisample; scalar_t__ GetPixelFormatAttribivARB; scalar_t__ SwapIntervalEXT; scalar_t__ CreateContextAttribsARB; scalar_t__ GetExtensionsStringARB; scalar_t__ GetExtensionsStringEXT; scalar_t__ instance; scalar_t__ ShareLists; scalar_t__ MakeCurrent; scalar_t__ GetCurrentContext; scalar_t__ GetCurrentDC; scalar_t__ GetProcAddress; scalar_t__ DeleteContext; scalar_t__ CreateContext; } ;
struct TYPE_8__ {int /*<<< orphan*/  helperWindowHandle; } ;
struct TYPE_11__ {TYPE_2__ wgl; TYPE_1__ win32; } ;
struct TYPE_10__ {int nSize; int nVersion; int dwFlags; int cColorBits; int /*<<< orphan*/  iPixelType; } ;
typedef  TYPE_3__ PIXELFORMATDESCRIPTOR ;
typedef  scalar_t__ PFN_wglShareLists ;
typedef  scalar_t__ PFN_wglMakeCurrent ;
typedef  scalar_t__ PFN_wglGetProcAddress ;
typedef  scalar_t__ PFN_wglGetCurrentDC ;
typedef  scalar_t__ PFN_wglGetCurrentContext ;
typedef  scalar_t__ PFN_wglDeleteContext ;
typedef  scalar_t__ PFN_wglCreateContext ;
typedef  scalar_t__ PFNWGLSWAPINTERVALEXTPROC ;
typedef  scalar_t__ PFNWGLGETPIXELFORMATATTRIBIVARBPROC ;
typedef  scalar_t__ PFNWGLGETEXTENSIONSSTRINGEXTPROC ;
typedef  scalar_t__ PFNWGLGETEXTENSIONSSTRINGARBPROC ;
typedef  scalar_t__ PFNWGLCREATECONTEXTATTRIBSARBPROC ;
typedef  int /*<<< orphan*/  HGLRC ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  GLFWbool ;

/* Variables and functions */
 int /*<<< orphan*/  ChoosePixelFormat (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  GLFW_FALSE ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 int /*<<< orphan*/  GLFW_TRUE ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 scalar_t__ GetProcAddress (scalar_t__,char*) ; 
 scalar_t__ LoadLibraryA (char*) ; 
 int PFD_DOUBLEBUFFER ; 
 int PFD_DRAW_TO_WINDOW ; 
 int PFD_SUPPORT_OPENGL ; 
 int /*<<< orphan*/  PFD_TYPE_RGBA ; 
 int /*<<< orphan*/  SetPixelFormat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_3__*,int) ; 
 TYPE_4__ _glfw ; 
 int /*<<< orphan*/  _glfwInputErrorWin32 (int /*<<< orphan*/ ,char*) ; 
 void* extensionSupportedWGL (char*) ; 
 int /*<<< orphan*/  wglCreateContext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wglDeleteContext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wglGetCurrentContext () ; 
 int /*<<< orphan*/  wglGetCurrentDC () ; 
 scalar_t__ wglGetProcAddress (char*) ; 
 int /*<<< orphan*/  wglMakeCurrent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

GLFWbool _glfwInitWGL(void)
{
    PIXELFORMATDESCRIPTOR pfd;
    HGLRC prc, rc;
    HDC pdc, dc;

    if (_glfw.wgl.instance)
        return GLFW_TRUE;

    _glfw.wgl.instance = LoadLibraryA("opengl32.dll");
    if (!_glfw.wgl.instance)
    {
        _glfwInputErrorWin32(GLFW_PLATFORM_ERROR,
                             "WGL: Failed to load opengl32.dll");
        return GLFW_FALSE;
    }

    _glfw.wgl.CreateContext = (PFN_wglCreateContext)
        GetProcAddress(_glfw.wgl.instance, "wglCreateContext");
    _glfw.wgl.DeleteContext = (PFN_wglDeleteContext)
        GetProcAddress(_glfw.wgl.instance, "wglDeleteContext");
    _glfw.wgl.GetProcAddress = (PFN_wglGetProcAddress)
        GetProcAddress(_glfw.wgl.instance, "wglGetProcAddress");
    _glfw.wgl.GetCurrentDC = (PFN_wglGetCurrentDC)
        GetProcAddress(_glfw.wgl.instance, "wglGetCurrentDC");
    _glfw.wgl.GetCurrentContext = (PFN_wglGetCurrentContext)
        GetProcAddress(_glfw.wgl.instance, "wglGetCurrentContext");
    _glfw.wgl.MakeCurrent = (PFN_wglMakeCurrent)
        GetProcAddress(_glfw.wgl.instance, "wglMakeCurrent");
    _glfw.wgl.ShareLists = (PFN_wglShareLists)
        GetProcAddress(_glfw.wgl.instance, "wglShareLists");

    // NOTE: A dummy context has to be created for opengl32.dll to load the
    //       OpenGL ICD, from which we can then query WGL extensions
    // NOTE: This code will accept the Microsoft GDI ICD; accelerated context
    //       creation failure occurs during manual pixel format enumeration

    dc = GetDC(_glfw.win32.helperWindowHandle);

    ZeroMemory(&pfd, sizeof(pfd));
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;

    if (!SetPixelFormat(dc, ChoosePixelFormat(dc, &pfd), &pfd))
    {
        _glfwInputErrorWin32(GLFW_PLATFORM_ERROR,
                             "WGL: Failed to set pixel format for dummy context");
        return GLFW_FALSE;
    }

    rc = wglCreateContext(dc);
    if (!rc)
    {
        _glfwInputErrorWin32(GLFW_PLATFORM_ERROR,
                             "WGL: Failed to create dummy context");
        return GLFW_FALSE;
    }

    pdc = wglGetCurrentDC();
    prc = wglGetCurrentContext();

    if (!wglMakeCurrent(dc, rc))
    {
        _glfwInputErrorWin32(GLFW_PLATFORM_ERROR,
                             "WGL: Failed to make dummy context current");
        wglMakeCurrent(pdc, prc);
        wglDeleteContext(rc);
        return GLFW_FALSE;
    }

    // NOTE: Functions must be loaded first as they're needed to retrieve the
    //       extension string that tells us whether the functions are supported
    _glfw.wgl.GetExtensionsStringEXT = (PFNWGLGETEXTENSIONSSTRINGEXTPROC)
        wglGetProcAddress("wglGetExtensionsStringEXT");
    _glfw.wgl.GetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC)
        wglGetProcAddress("wglGetExtensionsStringARB");
    _glfw.wgl.CreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)
        wglGetProcAddress("wglCreateContextAttribsARB");
    _glfw.wgl.SwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)
        wglGetProcAddress("wglSwapIntervalEXT");
    _glfw.wgl.GetPixelFormatAttribivARB = (PFNWGLGETPIXELFORMATATTRIBIVARBPROC)
        wglGetProcAddress("wglGetPixelFormatAttribivARB");

    // NOTE: WGL_ARB_extensions_string and WGL_EXT_extensions_string are not
    //       checked below as we are already using them
    _glfw.wgl.ARB_multisample =
        extensionSupportedWGL("WGL_ARB_multisample");
    _glfw.wgl.ARB_framebuffer_sRGB =
        extensionSupportedWGL("WGL_ARB_framebuffer_sRGB");
    _glfw.wgl.EXT_framebuffer_sRGB =
        extensionSupportedWGL("WGL_EXT_framebuffer_sRGB");
    _glfw.wgl.ARB_create_context =
        extensionSupportedWGL("WGL_ARB_create_context");
    _glfw.wgl.ARB_create_context_profile =
        extensionSupportedWGL("WGL_ARB_create_context_profile");
    _glfw.wgl.EXT_create_context_es2_profile =
        extensionSupportedWGL("WGL_EXT_create_context_es2_profile");
    _glfw.wgl.ARB_create_context_robustness =
        extensionSupportedWGL("WGL_ARB_create_context_robustness");
    _glfw.wgl.ARB_create_context_no_error =
        extensionSupportedWGL("WGL_ARB_create_context_no_error");
    _glfw.wgl.EXT_swap_control =
        extensionSupportedWGL("WGL_EXT_swap_control");
    _glfw.wgl.EXT_colorspace =
        extensionSupportedWGL("WGL_EXT_colorspace");
    _glfw.wgl.ARB_pixel_format =
        extensionSupportedWGL("WGL_ARB_pixel_format");
    _glfw.wgl.ARB_context_flush_control =
        extensionSupportedWGL("WGL_ARB_context_flush_control");

    wglMakeCurrent(pdc, prc);
    wglDeleteContext(rc);
    return GLFW_TRUE;
}