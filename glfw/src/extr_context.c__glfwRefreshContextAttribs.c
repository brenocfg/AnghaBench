#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ client; int major; int minor; int /*<<< orphan*/  (* swapBuffers ) (TYPE_2__*) ;scalar_t__ (* getProcAddress ) (char*) ;int /*<<< orphan*/  release; int /*<<< orphan*/  (* GetIntegerv ) (int /*<<< orphan*/ ,int*) ;void* robustness; void* profile; void* noerror; void* debug; void* forward; scalar_t__ GetStringi; int /*<<< orphan*/  revision; scalar_t__ (* GetString ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  source; } ;
struct TYPE_10__ {TYPE_1__ context; } ;
typedef  TYPE_2__ _GLFWwindow ;
struct TYPE_11__ {scalar_t__ client; int major; int minor; scalar_t__ debug; int /*<<< orphan*/  source; } ;
typedef  TYPE_3__ _GLFWctxconfig ;
struct TYPE_12__ {int /*<<< orphan*/  contextSlot; } ;
typedef  scalar_t__ (* PFNGLGETSTRINGPROC ) (int /*<<< orphan*/ ) ;
typedef  scalar_t__ PFNGLGETSTRINGIPROC ;
typedef  int /*<<< orphan*/  (* PFNGLGETINTEGERVPROC ) (int /*<<< orphan*/ ,int*) ;
typedef  int /*<<< orphan*/  (* PFNGLCLEARPROC ) (int /*<<< orphan*/ ) ;
typedef  int GLint ;
typedef  int /*<<< orphan*/  GLFWwindow ;
typedef  void* GLFWbool ;

/* Variables and functions */
 void* GLFW_FALSE ; 
 void* GLFW_LOSE_CONTEXT_ON_RESET ; 
 void* GLFW_NO_RESET_NOTIFICATION ; 
 scalar_t__ GLFW_OPENGL_API ; 
 void* GLFW_OPENGL_COMPAT_PROFILE ; 
 void* GLFW_OPENGL_CORE_PROFILE ; 
 scalar_t__ GLFW_OPENGL_ES_API ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 int /*<<< orphan*/  GLFW_RELEASE_BEHAVIOR_FLUSH ; 
 int /*<<< orphan*/  GLFW_RELEASE_BEHAVIOR_NONE ; 
 void* GLFW_TRUE ; 
 int /*<<< orphan*/  GLFW_VERSION_UNAVAILABLE ; 
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int GL_CONTEXT_COMPATIBILITY_PROFILE_BIT ; 
 int GL_CONTEXT_CORE_PROFILE_BIT ; 
 int /*<<< orphan*/  GL_CONTEXT_FLAGS ; 
 int GL_CONTEXT_FLAG_DEBUG_BIT ; 
 int GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT ; 
 int GL_CONTEXT_FLAG_NO_ERROR_BIT_KHR ; 
 int /*<<< orphan*/  GL_CONTEXT_PROFILE_MASK ; 
 int /*<<< orphan*/  GL_CONTEXT_RELEASE_BEHAVIOR ; 
 int GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH ; 
 int GL_LOSE_CONTEXT_ON_RESET_ARB ; 
 int GL_NONE ; 
 int GL_NO_RESET_NOTIFICATION_ARB ; 
 int /*<<< orphan*/  GL_RESET_NOTIFICATION_STRATEGY_ARB ; 
 int /*<<< orphan*/  GL_VERSION ; 
 TYPE_8__ _glfw ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_2__* _glfwPlatformGetTls (int /*<<< orphan*/ *) ; 
 scalar_t__ glfwExtensionSupported (char*) ; 
 int /*<<< orphan*/  glfwMakeContextCurrent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sscanf (char const*,char*,int*,int*,int /*<<< orphan*/ *) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,size_t const) ; 
 scalar_t__ stub1 (char*) ; 
 scalar_t__ stub10 (char*) ; 
 int /*<<< orphan*/  stub11 (TYPE_2__*) ; 
 scalar_t__ stub2 (char*) ; 
 scalar_t__ stub3 (int /*<<< orphan*/ ) ; 
 scalar_t__ stub4 (char*) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub9 (int /*<<< orphan*/ ,int*) ; 

GLFWbool _glfwRefreshContextAttribs(_GLFWwindow* window,
                                    const _GLFWctxconfig* ctxconfig)
{
    int i;
    _GLFWwindow* previous;
    const char* version;
    const char* prefixes[] =
    {
        "OpenGL ES-CM ",
        "OpenGL ES-CL ",
        "OpenGL ES ",
        NULL
    };

    window->context.source = ctxconfig->source;
    window->context.client = GLFW_OPENGL_API;

    previous = _glfwPlatformGetTls(&_glfw.contextSlot);
    glfwMakeContextCurrent((GLFWwindow*) window);

    window->context.GetIntegerv = (PFNGLGETINTEGERVPROC)
        window->context.getProcAddress("glGetIntegerv");
    window->context.GetString = (PFNGLGETSTRINGPROC)
        window->context.getProcAddress("glGetString");
    if (!window->context.GetIntegerv || !window->context.GetString)
    {
        _glfwInputError(GLFW_PLATFORM_ERROR, "Entry point retrieval is broken");
        glfwMakeContextCurrent((GLFWwindow*) previous);
        return GLFW_FALSE;
    }

    version = (const char*) window->context.GetString(GL_VERSION);
    if (!version)
    {
        if (ctxconfig->client == GLFW_OPENGL_API)
        {
            _glfwInputError(GLFW_PLATFORM_ERROR,
                            "OpenGL version string retrieval is broken");
        }
        else
        {
            _glfwInputError(GLFW_PLATFORM_ERROR,
                            "OpenGL ES version string retrieval is broken");
        }

        glfwMakeContextCurrent((GLFWwindow*) previous);
        return GLFW_FALSE;
    }

    for (i = 0;  prefixes[i];  i++)
    {
        const size_t length = strlen(prefixes[i]);

        if (strncmp(version, prefixes[i], length) == 0)
        {
            version += length;
            window->context.client = GLFW_OPENGL_ES_API;
            break;
        }
    }

    if (!sscanf(version, "%d.%d.%d",
                &window->context.major,
                &window->context.minor,
                &window->context.revision))
    {
        if (window->context.client == GLFW_OPENGL_API)
        {
            _glfwInputError(GLFW_PLATFORM_ERROR,
                            "No version found in OpenGL version string");
        }
        else
        {
            _glfwInputError(GLFW_PLATFORM_ERROR,
                            "No version found in OpenGL ES version string");
        }

        glfwMakeContextCurrent((GLFWwindow*) previous);
        return GLFW_FALSE;
    }

    if (window->context.major < ctxconfig->major ||
        (window->context.major == ctxconfig->major &&
         window->context.minor < ctxconfig->minor))
    {
        // The desired OpenGL version is greater than the actual version
        // This only happens if the machine lacks {GLX|WGL}_ARB_create_context
        // /and/ the user has requested an OpenGL version greater than 1.0

        // For API consistency, we emulate the behavior of the
        // {GLX|WGL}_ARB_create_context extension and fail here

        if (window->context.client == GLFW_OPENGL_API)
        {
            _glfwInputError(GLFW_VERSION_UNAVAILABLE,
                            "Requested OpenGL version %i.%i, got version %i.%i",
                            ctxconfig->major, ctxconfig->minor,
                            window->context.major, window->context.minor);
        }
        else
        {
            _glfwInputError(GLFW_VERSION_UNAVAILABLE,
                            "Requested OpenGL ES version %i.%i, got version %i.%i",
                            ctxconfig->major, ctxconfig->minor,
                            window->context.major, window->context.minor);
        }

        glfwMakeContextCurrent((GLFWwindow*) previous);
        return GLFW_FALSE;
    }

    if (window->context.major >= 3)
    {
        // OpenGL 3.0+ uses a different function for extension string retrieval
        // We cache it here instead of in glfwExtensionSupported mostly to alert
        // users as early as possible that their build may be broken

        window->context.GetStringi = (PFNGLGETSTRINGIPROC)
            window->context.getProcAddress("glGetStringi");
        if (!window->context.GetStringi)
        {
            _glfwInputError(GLFW_PLATFORM_ERROR,
                            "Entry point retrieval is broken");
            glfwMakeContextCurrent((GLFWwindow*) previous);
            return GLFW_FALSE;
        }
    }

    if (window->context.client == GLFW_OPENGL_API)
    {
        // Read back context flags (OpenGL 3.0 and above)
        if (window->context.major >= 3)
        {
            GLint flags;
            window->context.GetIntegerv(GL_CONTEXT_FLAGS, &flags);

            if (flags & GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT)
                window->context.forward = GLFW_TRUE;

            if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
                window->context.debug = GLFW_TRUE;
            else if (glfwExtensionSupported("GL_ARB_debug_output") &&
                     ctxconfig->debug)
            {
                // HACK: This is a workaround for older drivers (pre KHR_debug)
                //       not setting the debug bit in the context flags for
                //       debug contexts
                window->context.debug = GLFW_TRUE;
            }

            if (flags & GL_CONTEXT_FLAG_NO_ERROR_BIT_KHR)
                window->context.noerror = GLFW_TRUE;
        }

        // Read back OpenGL context profile (OpenGL 3.2 and above)
        if (window->context.major >= 4 ||
            (window->context.major == 3 && window->context.minor >= 2))
        {
            GLint mask;
            window->context.GetIntegerv(GL_CONTEXT_PROFILE_MASK, &mask);

            if (mask & GL_CONTEXT_COMPATIBILITY_PROFILE_BIT)
                window->context.profile = GLFW_OPENGL_COMPAT_PROFILE;
            else if (mask & GL_CONTEXT_CORE_PROFILE_BIT)
                window->context.profile = GLFW_OPENGL_CORE_PROFILE;
            else if (glfwExtensionSupported("GL_ARB_compatibility"))
            {
                // HACK: This is a workaround for the compatibility profile bit
                //       not being set in the context flags if an OpenGL 3.2+
                //       context was created without having requested a specific
                //       version
                window->context.profile = GLFW_OPENGL_COMPAT_PROFILE;
            }
        }

        // Read back robustness strategy
        if (glfwExtensionSupported("GL_ARB_robustness"))
        {
            // NOTE: We avoid using the context flags for detection, as they are
            //       only present from 3.0 while the extension applies from 1.1

            GLint strategy;
            window->context.GetIntegerv(GL_RESET_NOTIFICATION_STRATEGY_ARB,
                                        &strategy);

            if (strategy == GL_LOSE_CONTEXT_ON_RESET_ARB)
                window->context.robustness = GLFW_LOSE_CONTEXT_ON_RESET;
            else if (strategy == GL_NO_RESET_NOTIFICATION_ARB)
                window->context.robustness = GLFW_NO_RESET_NOTIFICATION;
        }
    }
    else
    {
        // Read back robustness strategy
        if (glfwExtensionSupported("GL_EXT_robustness"))
        {
            // NOTE: The values of these constants match those of the OpenGL ARB
            //       one, so we can reuse them here

            GLint strategy;
            window->context.GetIntegerv(GL_RESET_NOTIFICATION_STRATEGY_ARB,
                                        &strategy);

            if (strategy == GL_LOSE_CONTEXT_ON_RESET_ARB)
                window->context.robustness = GLFW_LOSE_CONTEXT_ON_RESET;
            else if (strategy == GL_NO_RESET_NOTIFICATION_ARB)
                window->context.robustness = GLFW_NO_RESET_NOTIFICATION;
        }
    }

    if (glfwExtensionSupported("GL_KHR_context_flush_control"))
    {
        GLint behavior;
        window->context.GetIntegerv(GL_CONTEXT_RELEASE_BEHAVIOR, &behavior);

        if (behavior == GL_NONE)
            window->context.release = GLFW_RELEASE_BEHAVIOR_NONE;
        else if (behavior == GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH)
            window->context.release = GLFW_RELEASE_BEHAVIOR_FLUSH;
    }

    // Clearing the front buffer to black to avoid garbage pixels left over from
    // previous uses of our bit of VRAM
    {
        PFNGLCLEARPROC glClear = (PFNGLCLEARPROC)
            window->context.getProcAddress("glClear");
        glClear(GL_COLOR_BUFFER_BIT);
        window->context.swapBuffers(window);
    }

    glfwMakeContextCurrent((GLFWwindow*) previous);
    return GLFW_TRUE;
}