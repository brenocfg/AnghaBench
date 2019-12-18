#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  crtc; } ;
struct TYPE_15__ {TYPE_2__ x11; } ;
typedef  TYPE_4__ _GLFWmonitor ;
typedef  int /*<<< orphan*/  XRRScreenResources ;
struct TYPE_16__ {int height; int width; } ;
typedef  TYPE_5__ XRRModeInfo ;
struct TYPE_17__ {int x; int y; scalar_t__ rotation; int /*<<< orphan*/  mode; } ;
typedef  TYPE_6__ XRRCrtcInfo ;
struct TYPE_12__ {int /*<<< orphan*/  monitorBroken; scalar_t__ available; } ;
struct TYPE_14__ {scalar_t__ NET_CURRENT_DESKTOP; int /*<<< orphan*/  root; scalar_t__ NET_WORKAREA; int /*<<< orphan*/  screen; int /*<<< orphan*/  display; TYPE_1__ randr; } ;
struct TYPE_18__ {TYPE_3__ x11; } ;
typedef  unsigned long const Atom ;

/* Variables and functions */
 int DisplayHeight (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int DisplayWidth (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RR_Rotate_270 ; 
 scalar_t__ RR_Rotate_90 ; 
 int /*<<< orphan*/  XA_CARDINAL ; 
 int /*<<< orphan*/  XFree (unsigned long const*) ; 
 int /*<<< orphan*/  XRRFreeCrtcInfo (TYPE_6__*) ; 
 int /*<<< orphan*/  XRRFreeScreenResources (int /*<<< orphan*/ *) ; 
 TYPE_6__* XRRGetCrtcInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * XRRGetScreenResourcesCurrent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_9__ _glfw ; 
 unsigned long _glfwGetWindowPropertyX11 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,unsigned char**) ; 
 TYPE_5__* getModeInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void _glfwPlatformGetMonitorWorkarea(_GLFWmonitor* monitor, int* xpos, int* ypos, int* width, int* height)
{
    int areaX = 0, areaY = 0, areaWidth = 0, areaHeight = 0;

    if (_glfw.x11.randr.available && !_glfw.x11.randr.monitorBroken)
    {
        XRRScreenResources* sr =
            XRRGetScreenResourcesCurrent(_glfw.x11.display, _glfw.x11.root);
        XRRCrtcInfo* ci = XRRGetCrtcInfo(_glfw.x11.display, sr, monitor->x11.crtc);

        areaX = ci->x;
        areaY = ci->y;

        const XRRModeInfo* mi = getModeInfo(sr, ci->mode);

        if (ci->rotation == RR_Rotate_90 || ci->rotation == RR_Rotate_270)
        {
            areaWidth  = mi->height;
            areaHeight = mi->width;
        }
        else
        {
            areaWidth  = mi->width;
            areaHeight = mi->height;
        }

        XRRFreeCrtcInfo(ci);
        XRRFreeScreenResources(sr);
    }
    else
    {
        areaWidth  = DisplayWidth(_glfw.x11.display, _glfw.x11.screen);
        areaHeight = DisplayHeight(_glfw.x11.display, _glfw.x11.screen);
    }

    if (_glfw.x11.NET_WORKAREA && _glfw.x11.NET_CURRENT_DESKTOP)
    {
        Atom* extents = NULL;
        Atom* desktop = NULL;
        const unsigned long extentCount =
            _glfwGetWindowPropertyX11(_glfw.x11.root,
                                      _glfw.x11.NET_WORKAREA,
                                      XA_CARDINAL,
                                      (unsigned char**) &extents);

        if (_glfwGetWindowPropertyX11(_glfw.x11.root,
                                      _glfw.x11.NET_CURRENT_DESKTOP,
                                      XA_CARDINAL,
                                      (unsigned char**) &desktop) > 0)
        {
            if (extentCount >= 4 && *desktop < extentCount / 4)
            {
                const int globalX = extents[*desktop * 4 + 0];
                const int globalY = extents[*desktop * 4 + 1];
                const int globalWidth  = extents[*desktop * 4 + 2];
                const int globalHeight = extents[*desktop * 4 + 3];

                if (areaX < globalX)
                {
                    areaWidth -= globalX - areaX;
                    areaX = globalX;
                }

                if (areaY < globalY)
                {
                    areaHeight -= globalY - areaY;
                    areaY = globalY;
                }

                if (areaX + areaWidth > globalX + globalWidth)
                    areaWidth = globalX - areaX + globalWidth;
                if (areaY + areaHeight > globalY + globalHeight)
                    areaHeight = globalY - areaY + globalHeight;
            }
        }

        if (extents)
            XFree(extents);
        if (desktop)
            XFree(desktop);
    }

    if (xpos)
        *xpos = areaX;
    if (ypos)
        *ypos = areaY;
    if (width)
        *width = areaWidth;
    if (height)
        *height = areaHeight;
}