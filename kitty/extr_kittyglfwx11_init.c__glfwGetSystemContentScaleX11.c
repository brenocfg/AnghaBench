#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  addr; } ;
typedef  TYPE_2__ XrmValue ;
typedef  scalar_t__ XrmDatabase ;
struct TYPE_5__ {int /*<<< orphan*/  display; int /*<<< orphan*/  RESOURCE_MANAGER; int /*<<< orphan*/  root; int /*<<< orphan*/  screen; } ;
struct TYPE_7__ {TYPE_1__ x11; } ;
typedef  scalar_t__ GLFWbool ;

/* Variables and functions */
 float DisplayHeight (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float DisplayHeightMM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float DisplayWidth (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float DisplayWidthMM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XA_STRING ; 
 int /*<<< orphan*/  XFree (char*) ; 
 char* XResourceManagerString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XrmDestroyDatabase (scalar_t__) ; 
 scalar_t__ XrmGetResource (scalar_t__,char*,char*,char**,TYPE_2__*) ; 
 scalar_t__ XrmGetStringDatabase (char*) ; 
 TYPE_3__ _glfw ; 
 int /*<<< orphan*/  _glfwGetWindowPropertyX11 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char**) ; 
 float atof (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 

void _glfwGetSystemContentScaleX11(float* xscale, float* yscale, GLFWbool bypass_cache)
{
    // NOTE: Default to the display-wide DPI as we don't currently have a policy
    //       for which monitor a window is considered to be on
    float xdpi = DisplayWidth(_glfw.x11.display, _glfw.x11.screen) *
        25.4f / DisplayWidthMM(_glfw.x11.display, _glfw.x11.screen);
    float ydpi = DisplayHeight(_glfw.x11.display, _glfw.x11.screen) *
        25.4f / DisplayHeightMM(_glfw.x11.display, _glfw.x11.screen);

    // NOTE: Basing the scale on Xft.dpi where available should provide the most
    //       consistent user experience (matches Qt, Gtk, etc), although not
    //       always the most accurate one
    char* rms = NULL;
    char* owned_rms = NULL;

    if (bypass_cache)
    {
        _glfwGetWindowPropertyX11(_glfw.x11.root,
                                  _glfw.x11.RESOURCE_MANAGER,
                                  XA_STRING,
                                  (unsigned char**) &owned_rms);
        rms = owned_rms;
    } else {
        rms = XResourceManagerString(_glfw.x11.display);
    }

    if (rms)
    {
        XrmDatabase db = XrmGetStringDatabase(rms);
        if (db)
        {
            XrmValue value;
            char* type = NULL;

            if (XrmGetResource(db, "Xft.dpi", "Xft.Dpi", &type, &value))
            {
                if (type && strcmp(type, "String") == 0)
                    xdpi = ydpi = atof(value.addr);
            }

            XrmDestroyDatabase(db);
        }
        XFree(owned_rms);
    }

    *xscale = xdpi / 96.f;
    *yscale = ydpi / 96.f;
}