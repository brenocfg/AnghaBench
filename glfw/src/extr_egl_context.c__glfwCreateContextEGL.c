#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_15__ ;

/* Type definitions */
struct TYPE_21__ {int /*<<< orphan*/  client; int /*<<< orphan*/  config; int /*<<< orphan*/  surface; int /*<<< orphan*/  handle; } ;
struct TYPE_22__ {int /*<<< orphan*/  destroy; int /*<<< orphan*/  getProcAddress; int /*<<< orphan*/  extensionSupported; int /*<<< orphan*/  swapInterval; int /*<<< orphan*/  swapBuffers; int /*<<< orphan*/  makeCurrent; TYPE_5__ egl; } ;
struct TYPE_23__ {TYPE_6__ context; } ;
typedef  TYPE_7__ _GLFWwindow ;
struct TYPE_24__ {scalar_t__ sRGB; } ;
typedef  TYPE_8__ _GLFWfbconfig ;
struct TYPE_25__ {scalar_t__ client; scalar_t__ profile; scalar_t__ robustness; int major; int minor; scalar_t__ release; scalar_t__ noerror; scalar_t__ debug; scalar_t__ forward; TYPE_3__* share; } ;
typedef  TYPE_9__ _GLFWctxconfig ;
struct TYPE_20__ {int prefix; int /*<<< orphan*/  KHR_get_all_proc_addresses; int /*<<< orphan*/  display; scalar_t__ KHR_gl_colorspace; scalar_t__ KHR_context_flush_control; scalar_t__ KHR_create_context_no_error; scalar_t__ KHR_create_context; } ;
struct TYPE_17__ {int /*<<< orphan*/ * handle; } ;
struct TYPE_18__ {TYPE_1__ egl; } ;
struct TYPE_19__ {TYPE_2__ context; } ;
struct TYPE_16__ {TYPE_4__ egl; } ;
typedef  int GLFWbool ;
typedef  int /*<<< orphan*/  EGLint ;
typedef  int /*<<< orphan*/ * EGLContext ;
typedef  int /*<<< orphan*/  EGLConfig ;

/* Variables and functions */
 int EGL_CONTEXT_CLIENT_VERSION ; 
 int EGL_CONTEXT_FLAGS_KHR ; 
 int EGL_CONTEXT_MAJOR_VERSION_KHR ; 
 int EGL_CONTEXT_MINOR_VERSION_KHR ; 
 int EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT_KHR ; 
 int EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR ; 
 int EGL_CONTEXT_OPENGL_DEBUG_BIT_KHR ; 
 int EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE_BIT_KHR ; 
 int EGL_CONTEXT_OPENGL_NO_ERROR_KHR ; 
 int EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR ; 
 int EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY_KHR ; 
 int EGL_CONTEXT_OPENGL_ROBUST_ACCESS_BIT_KHR ; 
 int EGL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_KHR ; 
 int EGL_CONTEXT_RELEASE_BEHAVIOR_KHR ; 
 int EGL_CONTEXT_RELEASE_BEHAVIOR_NONE_KHR ; 
 int EGL_GL_COLORSPACE_KHR ; 
 int EGL_GL_COLORSPACE_SRGB_KHR ; 
 int EGL_LOSE_CONTEXT_ON_RESET_KHR ; 
 int EGL_NONE ; 
 int /*<<< orphan*/  EGL_NO_CONTEXT ; 
 int EGL_NO_RESET_NOTIFICATION_KHR ; 
 int /*<<< orphan*/  EGL_NO_SURFACE ; 
 int /*<<< orphan*/  EGL_OPENGL_API ; 
 int /*<<< orphan*/  EGL_OPENGL_ES_API ; 
 int /*<<< orphan*/  GLFW_API_UNAVAILABLE ; 
 int GLFW_FALSE ; 
 int /*<<< orphan*/  GLFW_FORMAT_UNAVAILABLE ; 
 scalar_t__ GLFW_LOSE_CONTEXT_ON_RESET ; 
 scalar_t__ GLFW_NO_RESET_NOTIFICATION ; 
 scalar_t__ GLFW_OPENGL_API ; 
 scalar_t__ GLFW_OPENGL_COMPAT_PROFILE ; 
 scalar_t__ GLFW_OPENGL_CORE_PROFILE ; 
 scalar_t__ GLFW_OPENGL_ES_API ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 scalar_t__ GLFW_RELEASE_BEHAVIOR_FLUSH ; 
 scalar_t__ GLFW_RELEASE_BEHAVIOR_NONE ; 
 int GLFW_TRUE ; 
 int /*<<< orphan*/  GLFW_VERSION_UNAVAILABLE ; 
 int /*<<< orphan*/  _GLFW_EGL_NATIVE_WINDOW ; 
 char* _GLFW_GLESV1_LIBRARY ; 
 char* _GLFW_GLESV2_LIBRARY ; 
 char* _GLFW_OPENGL_LIBRARY ; 
 TYPE_15__ _glfw ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  _glfw_dlopen (char const*) ; 
 int /*<<< orphan*/  chooseEGLConfig (TYPE_9__ const*,TYPE_8__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroyContextEGL ; 
 int /*<<< orphan*/  eglBindAPI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eglCreateContext (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eglCreateWindowSurface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eglGetError () ; 
 int /*<<< orphan*/  extensionSupportedEGL ; 
 int /*<<< orphan*/  getEGLErrorString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getProcAddressEGL ; 
 int /*<<< orphan*/  makeContextCurrentEGL ; 
 int /*<<< orphan*/  setAttrib (int,int) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  swapBuffersEGL ; 
 int /*<<< orphan*/  swapIntervalEGL ; 

GLFWbool _glfwCreateContextEGL(_GLFWwindow* window,
                               const _GLFWctxconfig* ctxconfig,
                               const _GLFWfbconfig* fbconfig)
{
    EGLint attribs[40];
    EGLConfig config;
    EGLContext share = NULL;
    int index = 0;

    if (!_glfw.egl.display)
    {
        _glfwInputError(GLFW_API_UNAVAILABLE, "EGL: API not available");
        return GLFW_FALSE;
    }

    if (ctxconfig->share)
        share = ctxconfig->share->context.egl.handle;

    if (!chooseEGLConfig(ctxconfig, fbconfig, &config))
    {
        _glfwInputError(GLFW_FORMAT_UNAVAILABLE,
                        "EGL: Failed to find a suitable EGLConfig");
        return GLFW_FALSE;
    }

    if (ctxconfig->client == GLFW_OPENGL_ES_API)
    {
        if (!eglBindAPI(EGL_OPENGL_ES_API))
        {
            _glfwInputError(GLFW_API_UNAVAILABLE,
                            "EGL: Failed to bind OpenGL ES: %s",
                            getEGLErrorString(eglGetError()));
            return GLFW_FALSE;
        }
    }
    else
    {
        if (!eglBindAPI(EGL_OPENGL_API))
        {
            _glfwInputError(GLFW_API_UNAVAILABLE,
                            "EGL: Failed to bind OpenGL: %s",
                            getEGLErrorString(eglGetError()));
            return GLFW_FALSE;
        }
    }

    if (_glfw.egl.KHR_create_context)
    {
        int mask = 0, flags = 0;

        if (ctxconfig->client == GLFW_OPENGL_API)
        {
            if (ctxconfig->forward)
                flags |= EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE_BIT_KHR;

            if (ctxconfig->profile == GLFW_OPENGL_CORE_PROFILE)
                mask |= EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR;
            else if (ctxconfig->profile == GLFW_OPENGL_COMPAT_PROFILE)
                mask |= EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT_KHR;
        }

        if (ctxconfig->debug)
            flags |= EGL_CONTEXT_OPENGL_DEBUG_BIT_KHR;

        if (ctxconfig->robustness)
        {
            if (ctxconfig->robustness == GLFW_NO_RESET_NOTIFICATION)
            {
                setAttrib(EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY_KHR,
                          EGL_NO_RESET_NOTIFICATION_KHR);
            }
            else if (ctxconfig->robustness == GLFW_LOSE_CONTEXT_ON_RESET)
            {
                setAttrib(EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY_KHR,
                          EGL_LOSE_CONTEXT_ON_RESET_KHR);
            }

            flags |= EGL_CONTEXT_OPENGL_ROBUST_ACCESS_BIT_KHR;
        }

        if (ctxconfig->noerror)
        {
            if (_glfw.egl.KHR_create_context_no_error)
                setAttrib(EGL_CONTEXT_OPENGL_NO_ERROR_KHR, GLFW_TRUE);
        }

        if (ctxconfig->major != 1 || ctxconfig->minor != 0)
        {
            setAttrib(EGL_CONTEXT_MAJOR_VERSION_KHR, ctxconfig->major);
            setAttrib(EGL_CONTEXT_MINOR_VERSION_KHR, ctxconfig->minor);
        }

        if (mask)
            setAttrib(EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR, mask);

        if (flags)
            setAttrib(EGL_CONTEXT_FLAGS_KHR, flags);
    }
    else
    {
        if (ctxconfig->client == GLFW_OPENGL_ES_API)
            setAttrib(EGL_CONTEXT_CLIENT_VERSION, ctxconfig->major);
    }

    if (_glfw.egl.KHR_context_flush_control)
    {
        if (ctxconfig->release == GLFW_RELEASE_BEHAVIOR_NONE)
        {
            setAttrib(EGL_CONTEXT_RELEASE_BEHAVIOR_KHR,
                      EGL_CONTEXT_RELEASE_BEHAVIOR_NONE_KHR);
        }
        else if (ctxconfig->release == GLFW_RELEASE_BEHAVIOR_FLUSH)
        {
            setAttrib(EGL_CONTEXT_RELEASE_BEHAVIOR_KHR,
                      EGL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_KHR);
        }
    }

    setAttrib(EGL_NONE, EGL_NONE);

    window->context.egl.handle = eglCreateContext(_glfw.egl.display,
                                                  config, share, attribs);

    if (window->context.egl.handle == EGL_NO_CONTEXT)
    {
        _glfwInputError(GLFW_VERSION_UNAVAILABLE,
                        "EGL: Failed to create context: %s",
                        getEGLErrorString(eglGetError()));
        return GLFW_FALSE;
    }

    // Set up attributes for surface creation
    {
        int index = 0;

        if (fbconfig->sRGB)
        {
            if (_glfw.egl.KHR_gl_colorspace)
                setAttrib(EGL_GL_COLORSPACE_KHR, EGL_GL_COLORSPACE_SRGB_KHR);
        }

        setAttrib(EGL_NONE, EGL_NONE);
    }

    window->context.egl.surface =
        eglCreateWindowSurface(_glfw.egl.display,
                               config,
                               _GLFW_EGL_NATIVE_WINDOW,
                               attribs);
    if (window->context.egl.surface == EGL_NO_SURFACE)
    {
        _glfwInputError(GLFW_PLATFORM_ERROR,
                        "EGL: Failed to create window surface: %s",
                        getEGLErrorString(eglGetError()));
        return GLFW_FALSE;
    }

    window->context.egl.config = config;

    // Load the appropriate client library
    if (!_glfw.egl.KHR_get_all_proc_addresses)
    {
        int i;
        const char** sonames;
        const char* es1sonames[] =
        {
#if defined(_GLFW_GLESV1_LIBRARY)
            _GLFW_GLESV1_LIBRARY,
#elif defined(_GLFW_WIN32)
            "GLESv1_CM.dll",
            "libGLES_CM.dll",
#elif defined(_GLFW_COCOA)
            "libGLESv1_CM.dylib",
#else
            "libGLESv1_CM.so.1",
            "libGLES_CM.so.1",
#endif
            NULL
        };
        const char* es2sonames[] =
        {
#if defined(_GLFW_GLESV2_LIBRARY)
            _GLFW_GLESV2_LIBRARY,
#elif defined(_GLFW_WIN32)
            "GLESv2.dll",
            "libGLESv2.dll",
#elif defined(_GLFW_COCOA)
            "libGLESv2.dylib",
#elif defined(__CYGWIN__)
            "libGLESv2-2.so",
#else
            "libGLESv2.so.2",
#endif
            NULL
        };
        const char* glsonames[] =
        {
#if defined(_GLFW_OPENGL_LIBRARY)
            _GLFW_OPENGL_LIBRARY,
#elif defined(_GLFW_WIN32)
#elif defined(_GLFW_COCOA)
#else
            "libGL.so.1",
#endif
            NULL
        };

        if (ctxconfig->client == GLFW_OPENGL_ES_API)
        {
            if (ctxconfig->major == 1)
                sonames = es1sonames;
            else
                sonames = es2sonames;
        }
        else
            sonames = glsonames;

        for (i = 0;  sonames[i];  i++)
        {
            // HACK: Match presence of lib prefix to increase chance of finding
            //       a matching pair in the jungle that is Win32 EGL/GLES
            if (_glfw.egl.prefix != (strncmp(sonames[i], "lib", 3) == 0))
                continue;

            window->context.egl.client = _glfw_dlopen(sonames[i]);
            if (window->context.egl.client)
                break;
        }

        if (!window->context.egl.client)
        {
            _glfwInputError(GLFW_API_UNAVAILABLE,
                            "EGL: Failed to load client library");
            return GLFW_FALSE;
        }
    }

    window->context.makeCurrent = makeContextCurrentEGL;
    window->context.swapBuffers = swapBuffersEGL;
    window->context.swapInterval = swapIntervalEGL;
    window->context.extensionSupported = extensionSupportedEGL;
    window->context.getProcAddress = getProcAddressEGL;
    window->context.destroy = destroyContextEGL;

    return GLFW_TRUE;
}