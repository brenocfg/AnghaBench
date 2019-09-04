#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_8__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_23__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
struct TYPE_24__ {int /*<<< orphan*/  appId; } ;
struct TYPE_29__ {scalar_t__ visible; scalar_t__ title; TYPE_1__ wl; } ;
typedef  TYPE_5__ _GLFWwndconfig ;
struct TYPE_27__ {int /*<<< orphan*/ * toplevel; int /*<<< orphan*/ * surface; } ;
struct TYPE_28__ {int visible; int monitorsSize; scalar_t__ monitorsCount; int /*<<< orphan*/  monitors; int /*<<< orphan*/ * currentCursor; int /*<<< orphan*/ * shellSurface; TYPE_3__ xdg; int /*<<< orphan*/  title; int /*<<< orphan*/  appId; int /*<<< orphan*/  transparent; } ;
struct TYPE_30__ {TYPE_4__ wl; } ;
typedef  TYPE_6__ _GLFWwindow ;
typedef  int /*<<< orphan*/  _GLFWmonitor ;
struct TYPE_31__ {int /*<<< orphan*/  transparent; } ;
typedef  TYPE_7__ _GLFWfbconfig ;
struct TYPE_32__ {scalar_t__ client; scalar_t__ source; } ;
typedef  TYPE_8__ _GLFWctxconfig ;
struct TYPE_26__ {scalar_t__ wmBase; } ;
struct TYPE_25__ {TYPE_2__ wl; } ;

/* Variables and functions */
 scalar_t__ GLFW_EGL_CONTEXT_API ; 
 int GLFW_FALSE ; 
 scalar_t__ GLFW_NATIVE_CONTEXT_API ; 
 scalar_t__ GLFW_NO_API ; 
 scalar_t__ GLFW_OSMESA_CONTEXT_API ; 
 int GLFW_TRUE ; 
 TYPE_23__ _glfw ; 
 int /*<<< orphan*/  _glfwCreateContextEGL (TYPE_6__*,TYPE_8__ const*,TYPE_7__ const*) ; 
 int /*<<< orphan*/  _glfwCreateContextOSMesa (TYPE_6__*,TYPE_8__ const*,TYPE_7__ const*) ; 
 int /*<<< orphan*/  _glfwInitEGL () ; 
 int /*<<< orphan*/  _glfwInitOSMesa () ; 
 int /*<<< orphan*/  _glfw_strdup (scalar_t__) ; 
 int /*<<< orphan*/  calloc (int,int) ; 
 int /*<<< orphan*/  createShellSurface (TYPE_6__*) ; 
 int /*<<< orphan*/  createSurface (TYPE_6__*,TYPE_5__ const*) ; 
 int /*<<< orphan*/  createXdgSurface (TYPE_6__*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int _glfwPlatformCreateWindow(_GLFWwindow* window,
                              const _GLFWwndconfig* wndconfig,
                              const _GLFWctxconfig* ctxconfig,
                              const _GLFWfbconfig* fbconfig)
{
    window->wl.transparent = fbconfig->transparent;
    strncpy(window->wl.appId, wndconfig->wl.appId, sizeof(window->wl.appId));

    if (!createSurface(window, wndconfig))
        return GLFW_FALSE;

    if (ctxconfig->client != GLFW_NO_API)
    {
        if (ctxconfig->source == GLFW_EGL_CONTEXT_API ||
            ctxconfig->source == GLFW_NATIVE_CONTEXT_API)
        {
            if (!_glfwInitEGL())
                return GLFW_FALSE;
            if (!_glfwCreateContextEGL(window, ctxconfig, fbconfig))
                return GLFW_FALSE;
        }
        else if (ctxconfig->source == GLFW_OSMESA_CONTEXT_API)
        {
            if (!_glfwInitOSMesa())
                return GLFW_FALSE;
            if (!_glfwCreateContextOSMesa(window, ctxconfig, fbconfig))
                return GLFW_FALSE;
        }
    }

    if (wndconfig->title)
        window->wl.title = _glfw_strdup(wndconfig->title);

    if (wndconfig->visible)
    {
        if (_glfw.wl.wmBase)
        {
            if (!createXdgSurface(window))
                return GLFW_FALSE;
        }
        else
        {
            if (!createShellSurface(window))
                return GLFW_FALSE;
        }

        window->wl.visible = GLFW_TRUE;
    }
    else
    {
        window->wl.xdg.surface = NULL;
        window->wl.xdg.toplevel = NULL;
        window->wl.shellSurface = NULL;
        window->wl.visible = GLFW_FALSE;
    }

    window->wl.currentCursor = NULL;

    window->wl.monitors = calloc(1, sizeof(_GLFWmonitor*));
    window->wl.monitorsCount = 0;
    window->wl.monitorsSize = 1;

    return GLFW_TRUE;
}