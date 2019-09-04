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
typedef  struct TYPE_16__   TYPE_14__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct TYPE_23__ {int /*<<< orphan*/  window; void* handle; } ;
struct TYPE_24__ {int /*<<< orphan*/  destroy; int /*<<< orphan*/  getProcAddress; int /*<<< orphan*/  extensionSupported; int /*<<< orphan*/  swapInterval; int /*<<< orphan*/  swapBuffers; int /*<<< orphan*/  makeCurrent; TYPE_7__ glx; } ;
struct TYPE_22__ {int /*<<< orphan*/  handle; } ;
struct TYPE_25__ {TYPE_8__ context; TYPE_6__ x11; } ;
typedef  TYPE_9__ _GLFWwindow ;
typedef  int /*<<< orphan*/  _GLFWfbconfig ;
struct TYPE_15__ {scalar_t__ client; scalar_t__ forward; scalar_t__ profile; scalar_t__ robustness; scalar_t__ release; int major; int minor; scalar_t__ noerror; scalar_t__ debug; TYPE_3__* share; } ;
typedef  TYPE_10__ _GLFWctxconfig ;
struct TYPE_21__ {scalar_t__ errorCode; int /*<<< orphan*/  display; } ;
struct TYPE_20__ {scalar_t__ errorBase; void* (* CreateContextAttribsARB ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ;scalar_t__ ARB_create_context_no_error; scalar_t__ ARB_context_flush_control; scalar_t__ ARB_create_context_robustness; scalar_t__ ARB_create_context; int /*<<< orphan*/  ARB_create_context_profile; int /*<<< orphan*/  EXT_create_context_es2_profile; } ;
struct TYPE_17__ {int /*<<< orphan*/ * handle; } ;
struct TYPE_18__ {TYPE_1__ glx; } ;
struct TYPE_19__ {TYPE_2__ context; } ;
struct TYPE_16__ {TYPE_5__ x11; TYPE_4__ glx; } ;
typedef  int /*<<< orphan*/ * GLXFBConfig ;
typedef  int /*<<< orphan*/ * GLXContext ;
typedef  scalar_t__ GLFWbool ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_API_UNAVAILABLE ; 
 scalar_t__ GLFW_FALSE ; 
 int /*<<< orphan*/  GLFW_FORMAT_UNAVAILABLE ; 
 scalar_t__ GLFW_LOSE_CONTEXT_ON_RESET ; 
 scalar_t__ GLFW_NO_RESET_NOTIFICATION ; 
 scalar_t__ GLFW_OPENGL_ANY_PROFILE ; 
 scalar_t__ GLFW_OPENGL_API ; 
 scalar_t__ GLFW_OPENGL_COMPAT_PROFILE ; 
 scalar_t__ GLFW_OPENGL_CORE_PROFILE ; 
 scalar_t__ GLFW_OPENGL_ES_API ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 scalar_t__ GLFW_RELEASE_BEHAVIOR_FLUSH ; 
 scalar_t__ GLFW_RELEASE_BEHAVIOR_NONE ; 
 scalar_t__ GLFW_TRUE ; 
 int /*<<< orphan*/  GLFW_VERSION_UNAVAILABLE ; 
 scalar_t__ GLXBadProfileARB ; 
 int GLX_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB ; 
 int GLX_CONTEXT_CORE_PROFILE_BIT_ARB ; 
 int GLX_CONTEXT_DEBUG_BIT_ARB ; 
 int GLX_CONTEXT_ES2_PROFILE_BIT_EXT ; 
 int GLX_CONTEXT_FLAGS_ARB ; 
 int GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB ; 
 int GLX_CONTEXT_MAJOR_VERSION_ARB ; 
 int GLX_CONTEXT_MINOR_VERSION_ARB ; 
 int GLX_CONTEXT_OPENGL_NO_ERROR_ARB ; 
 int GLX_CONTEXT_PROFILE_MASK_ARB ; 
 int GLX_CONTEXT_RELEASE_BEHAVIOR_ARB ; 
 int GLX_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB ; 
 int GLX_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB ; 
 int GLX_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB ; 
 int GLX_CONTEXT_ROBUST_ACCESS_BIT_ARB ; 
 int GLX_LOSE_CONTEXT_ON_RESET_ARB ; 
 int GLX_NO_RESET_NOTIFICATION_ARB ; 
 int None ; 
 int /*<<< orphan*/  True ; 
 TYPE_14__ _glfw ; 
 int /*<<< orphan*/  _glfwGrabErrorHandlerX11 () ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _glfwInputErrorX11 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _glfwReleaseErrorHandlerX11 () ; 
 int /*<<< orphan*/  chooseGLXFBConfig (int /*<<< orphan*/  const*,int /*<<< orphan*/ **) ; 
 void* createLegacyContextGLX (TYPE_9__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroyContextGLX ; 
 int /*<<< orphan*/  extensionSupportedGLX ; 
 int /*<<< orphan*/  getProcAddressGLX ; 
 int /*<<< orphan*/  glXCreateWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  makeContextCurrentGLX ; 
 int /*<<< orphan*/  setAttrib (int,int) ; 
 void* stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  swapBuffersGLX ; 
 int /*<<< orphan*/  swapIntervalGLX ; 

GLFWbool _glfwCreateContextGLX(_GLFWwindow* window,
                               const _GLFWctxconfig* ctxconfig,
                               const _GLFWfbconfig* fbconfig)
{
    int attribs[40];
    GLXFBConfig native = NULL;
    GLXContext share = NULL;

    if (ctxconfig->share)
        share = ctxconfig->share->context.glx.handle;

    if (!chooseGLXFBConfig(fbconfig, &native))
    {
        _glfwInputError(GLFW_FORMAT_UNAVAILABLE,
                        "GLX: Failed to find a suitable GLXFBConfig");
        return GLFW_FALSE;
    }

    if (ctxconfig->client == GLFW_OPENGL_ES_API)
    {
        if (!_glfw.glx.ARB_create_context ||
            !_glfw.glx.ARB_create_context_profile ||
            !_glfw.glx.EXT_create_context_es2_profile)
        {
            _glfwInputError(GLFW_API_UNAVAILABLE,
                            "GLX: OpenGL ES requested but GLX_EXT_create_context_es2_profile is unavailable");
            return GLFW_FALSE;
        }
    }

    if (ctxconfig->forward)
    {
        if (!_glfw.glx.ARB_create_context)
        {
            _glfwInputError(GLFW_VERSION_UNAVAILABLE,
                            "GLX: Forward compatibility requested but GLX_ARB_create_context_profile is unavailable");
            return GLFW_FALSE;
        }
    }

    if (ctxconfig->profile)
    {
        if (!_glfw.glx.ARB_create_context ||
            !_glfw.glx.ARB_create_context_profile)
        {
            _glfwInputError(GLFW_VERSION_UNAVAILABLE,
                            "GLX: An OpenGL profile requested but GLX_ARB_create_context_profile is unavailable");
            return GLFW_FALSE;
        }
    }

    _glfwGrabErrorHandlerX11();

    if (_glfw.glx.ARB_create_context)
    {
        int index = 0, mask = 0, flags = 0;

        if (ctxconfig->client == GLFW_OPENGL_API)
        {
            if (ctxconfig->forward)
                flags |= GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB;

            if (ctxconfig->profile == GLFW_OPENGL_CORE_PROFILE)
                mask |= GLX_CONTEXT_CORE_PROFILE_BIT_ARB;
            else if (ctxconfig->profile == GLFW_OPENGL_COMPAT_PROFILE)
                mask |= GLX_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB;
        }
        else
            mask |= GLX_CONTEXT_ES2_PROFILE_BIT_EXT;

        if (ctxconfig->debug)
            flags |= GLX_CONTEXT_DEBUG_BIT_ARB;

        if (ctxconfig->robustness)
        {
            if (_glfw.glx.ARB_create_context_robustness)
            {
                if (ctxconfig->robustness == GLFW_NO_RESET_NOTIFICATION)
                {
                    setAttrib(GLX_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB,
                              GLX_NO_RESET_NOTIFICATION_ARB);
                }
                else if (ctxconfig->robustness == GLFW_LOSE_CONTEXT_ON_RESET)
                {
                    setAttrib(GLX_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB,
                              GLX_LOSE_CONTEXT_ON_RESET_ARB);
                }

                flags |= GLX_CONTEXT_ROBUST_ACCESS_BIT_ARB;
            }
        }

        if (ctxconfig->release)
        {
            if (_glfw.glx.ARB_context_flush_control)
            {
                if (ctxconfig->release == GLFW_RELEASE_BEHAVIOR_NONE)
                {
                    setAttrib(GLX_CONTEXT_RELEASE_BEHAVIOR_ARB,
                              GLX_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB);
                }
                else if (ctxconfig->release == GLFW_RELEASE_BEHAVIOR_FLUSH)
                {
                    setAttrib(GLX_CONTEXT_RELEASE_BEHAVIOR_ARB,
                              GLX_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB);
                }
            }
        }

        if (ctxconfig->noerror)
        {
            if (_glfw.glx.ARB_create_context_no_error)
                setAttrib(GLX_CONTEXT_OPENGL_NO_ERROR_ARB, GLFW_TRUE);
        }

        // NOTE: Only request an explicitly versioned context when necessary, as
        //       explicitly requesting version 1.0 does not always return the
        //       highest version supported by the driver
        if (ctxconfig->major != 1 || ctxconfig->minor != 0)
        {
            setAttrib(GLX_CONTEXT_MAJOR_VERSION_ARB, ctxconfig->major);
            setAttrib(GLX_CONTEXT_MINOR_VERSION_ARB, ctxconfig->minor);
        }

        if (mask)
            setAttrib(GLX_CONTEXT_PROFILE_MASK_ARB, mask);

        if (flags)
            setAttrib(GLX_CONTEXT_FLAGS_ARB, flags);

        setAttrib(None, None);

        window->context.glx.handle =
            _glfw.glx.CreateContextAttribsARB(_glfw.x11.display,
                                              native,
                                              share,
                                              True,
                                              attribs);

        // HACK: This is a fallback for broken versions of the Mesa
        //       implementation of GLX_ARB_create_context_profile that fail
        //       default 1.0 context creation with a GLXBadProfileARB error in
        //       violation of the extension spec
        if (!window->context.glx.handle)
        {
            if (_glfw.x11.errorCode == _glfw.glx.errorBase + GLXBadProfileARB &&
                ctxconfig->client == GLFW_OPENGL_API &&
                ctxconfig->profile == GLFW_OPENGL_ANY_PROFILE &&
                ctxconfig->forward == GLFW_FALSE)
            {
                window->context.glx.handle =
                    createLegacyContextGLX(window, native, share);
            }
        }
    }
    else
    {
        window->context.glx.handle =
            createLegacyContextGLX(window, native, share);
    }

    _glfwReleaseErrorHandlerX11();

    if (!window->context.glx.handle)
    {
        _glfwInputErrorX11(GLFW_VERSION_UNAVAILABLE, "GLX: Failed to create context");
        return GLFW_FALSE;
    }

    window->context.glx.window =
        glXCreateWindow(_glfw.x11.display, native, window->x11.handle, NULL);
    if (!window->context.glx.window)
    {
        _glfwInputError(GLFW_PLATFORM_ERROR, "GLX: Failed to create window");
        return GLFW_FALSE;
    }

    window->context.makeCurrent = makeContextCurrentGLX;
    window->context.swapBuffers = swapBuffersGLX;
    window->context.swapInterval = swapIntervalGLX;
    window->context.extensionSupported = extensionSupportedGLX;
    window->context.getProcAddress = getProcAddressGLX;
    window->context.destroy = destroyContextGLX;

    return GLFW_TRUE;
}