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
struct TYPE_3__ {int prefix; scalar_t__ display; void* KHR_context_flush_control; void* KHR_get_all_proc_addresses; void* KHR_gl_colorspace; void* KHR_create_context_no_error; void* KHR_create_context; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; scalar_t__ GetProcAddress; scalar_t__ QueryString; scalar_t__ SwapInterval; scalar_t__ SwapBuffers; scalar_t__ MakeCurrent; scalar_t__ CreateWindowSurface; scalar_t__ DestroyContext; scalar_t__ DestroySurface; scalar_t__ CreateContext; scalar_t__ BindAPI; scalar_t__ Terminate; scalar_t__ Initialize; scalar_t__ GetError; scalar_t__ GetDisplay; scalar_t__ GetConfigs; scalar_t__ GetConfigAttrib; scalar_t__ handle; } ;
struct TYPE_4__ {TYPE_1__ egl; } ;
typedef  scalar_t__ PFN_eglTerminate ;
typedef  scalar_t__ PFN_eglSwapInterval ;
typedef  scalar_t__ PFN_eglSwapBuffers ;
typedef  scalar_t__ PFN_eglQueryString ;
typedef  scalar_t__ PFN_eglMakeCurrent ;
typedef  scalar_t__ PFN_eglInitialize ;
typedef  scalar_t__ PFN_eglGetProcAddress ;
typedef  scalar_t__ PFN_eglGetError ;
typedef  scalar_t__ PFN_eglGetDisplay ;
typedef  scalar_t__ PFN_eglGetConfigs ;
typedef  scalar_t__ PFN_eglGetConfigAttrib ;
typedef  scalar_t__ PFN_eglDestroySurface ;
typedef  scalar_t__ PFN_eglDestroyContext ;
typedef  scalar_t__ PFN_eglCreateWindowSurface ;
typedef  scalar_t__ PFN_eglCreateContext ;
typedef  scalar_t__ PFN_eglBindAPI ;
typedef  int /*<<< orphan*/  GLFWbool ;

/* Variables and functions */
 scalar_t__ EGL_NO_DISPLAY ; 
 int /*<<< orphan*/  GLFW_API_UNAVAILABLE ; 
 int /*<<< orphan*/  GLFW_FALSE ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 int /*<<< orphan*/  GLFW_TRUE ; 
 char* _GLFW_EGL_LIBRARY ; 
 int /*<<< orphan*/  _GLFW_EGL_NATIVE_DISPLAY ; 
 TYPE_2__ _glfw ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  _glfwTerminateEGL () ; 
 scalar_t__ _glfw_dlopen (char const*) ; 
 scalar_t__ _glfw_dlsym (scalar_t__,char*) ; 
 scalar_t__ eglGetDisplay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eglGetError () ; 
 int /*<<< orphan*/  eglInitialize (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* extensionSupportedEGL (char*) ; 
 int /*<<< orphan*/  getEGLErrorString (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

GLFWbool _glfwInitEGL(void)
{
    int i;
    const char* sonames[] =
    {
#if defined(_GLFW_EGL_LIBRARY)
        _GLFW_EGL_LIBRARY,
#elif defined(_GLFW_WIN32)
        "libEGL.dll",
        "EGL.dll",
#elif defined(_GLFW_COCOA)
        "libEGL.dylib",
#elif defined(__CYGWIN__)
        "libEGL-1.so",
#else
        "libEGL.so.1",
#endif
        NULL
    };

    if (_glfw.egl.handle)
        return GLFW_TRUE;

    for (i = 0;  sonames[i];  i++)
    {
        _glfw.egl.handle = _glfw_dlopen(sonames[i]);
        if (_glfw.egl.handle)
            break;
    }

    if (!_glfw.egl.handle)
    {
        _glfwInputError(GLFW_API_UNAVAILABLE, "EGL: Library not found");
        return GLFW_FALSE;
    }

    _glfw.egl.prefix = (strncmp(sonames[i], "lib", 3) == 0);

    _glfw.egl.GetConfigAttrib = (PFN_eglGetConfigAttrib)
        _glfw_dlsym(_glfw.egl.handle, "eglGetConfigAttrib");
    _glfw.egl.GetConfigs = (PFN_eglGetConfigs)
        _glfw_dlsym(_glfw.egl.handle, "eglGetConfigs");
    _glfw.egl.GetDisplay = (PFN_eglGetDisplay)
        _glfw_dlsym(_glfw.egl.handle, "eglGetDisplay");
    _glfw.egl.GetError = (PFN_eglGetError)
        _glfw_dlsym(_glfw.egl.handle, "eglGetError");
    _glfw.egl.Initialize = (PFN_eglInitialize)
        _glfw_dlsym(_glfw.egl.handle, "eglInitialize");
    _glfw.egl.Terminate = (PFN_eglTerminate)
        _glfw_dlsym(_glfw.egl.handle, "eglTerminate");
    _glfw.egl.BindAPI = (PFN_eglBindAPI)
        _glfw_dlsym(_glfw.egl.handle, "eglBindAPI");
    _glfw.egl.CreateContext = (PFN_eglCreateContext)
        _glfw_dlsym(_glfw.egl.handle, "eglCreateContext");
    _glfw.egl.DestroySurface = (PFN_eglDestroySurface)
        _glfw_dlsym(_glfw.egl.handle, "eglDestroySurface");
    _glfw.egl.DestroyContext = (PFN_eglDestroyContext)
        _glfw_dlsym(_glfw.egl.handle, "eglDestroyContext");
    _glfw.egl.CreateWindowSurface = (PFN_eglCreateWindowSurface)
        _glfw_dlsym(_glfw.egl.handle, "eglCreateWindowSurface");
    _glfw.egl.MakeCurrent = (PFN_eglMakeCurrent)
        _glfw_dlsym(_glfw.egl.handle, "eglMakeCurrent");
    _glfw.egl.SwapBuffers = (PFN_eglSwapBuffers)
        _glfw_dlsym(_glfw.egl.handle, "eglSwapBuffers");
    _glfw.egl.SwapInterval = (PFN_eglSwapInterval)
        _glfw_dlsym(_glfw.egl.handle, "eglSwapInterval");
    _glfw.egl.QueryString = (PFN_eglQueryString)
        _glfw_dlsym(_glfw.egl.handle, "eglQueryString");
    _glfw.egl.GetProcAddress = (PFN_eglGetProcAddress)
        _glfw_dlsym(_glfw.egl.handle, "eglGetProcAddress");

    if (!_glfw.egl.GetConfigAttrib ||
        !_glfw.egl.GetConfigs ||
        !_glfw.egl.GetDisplay ||
        !_glfw.egl.GetError ||
        !_glfw.egl.Initialize ||
        !_glfw.egl.Terminate ||
        !_glfw.egl.BindAPI ||
        !_glfw.egl.CreateContext ||
        !_glfw.egl.DestroySurface ||
        !_glfw.egl.DestroyContext ||
        !_glfw.egl.CreateWindowSurface ||
        !_glfw.egl.MakeCurrent ||
        !_glfw.egl.SwapBuffers ||
        !_glfw.egl.SwapInterval ||
        !_glfw.egl.QueryString ||
        !_glfw.egl.GetProcAddress)
    {
        _glfwInputError(GLFW_PLATFORM_ERROR,
                        "EGL: Failed to load required entry points");

        _glfwTerminateEGL();
        return GLFW_FALSE;
    }

    _glfw.egl.display = eglGetDisplay(_GLFW_EGL_NATIVE_DISPLAY);
    if (_glfw.egl.display == EGL_NO_DISPLAY)
    {
        _glfwInputError(GLFW_API_UNAVAILABLE,
                        "EGL: Failed to get EGL display: %s",
                        getEGLErrorString(eglGetError()));

        _glfwTerminateEGL();
        return GLFW_FALSE;
    }

    if (!eglInitialize(_glfw.egl.display, &_glfw.egl.major, &_glfw.egl.minor))
    {
        _glfwInputError(GLFW_API_UNAVAILABLE,
                        "EGL: Failed to initialize EGL: %s",
                        getEGLErrorString(eglGetError()));

        _glfwTerminateEGL();
        return GLFW_FALSE;
    }

    _glfw.egl.KHR_create_context =
        extensionSupportedEGL("EGL_KHR_create_context");
    _glfw.egl.KHR_create_context_no_error =
        extensionSupportedEGL("EGL_KHR_create_context_no_error");
    _glfw.egl.KHR_gl_colorspace =
        extensionSupportedEGL("EGL_KHR_gl_colorspace");
    _glfw.egl.KHR_get_all_proc_addresses =
        extensionSupportedEGL("EGL_KHR_get_all_proc_addresses");
    _glfw.egl.KHR_context_flush_control =
        extensionSupportedEGL("EGL_KHR_context_flush_control");

    return GLFW_TRUE;
}