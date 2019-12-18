#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ alphaMask; } ;
struct TYPE_10__ {TYPE_3__ direct; } ;
typedef  TYPE_4__ XRenderPictFormat ;
typedef  int /*<<< orphan*/  Visual ;
struct TYPE_7__ {int /*<<< orphan*/  available; } ;
struct TYPE_8__ {int /*<<< orphan*/  display; TYPE_1__ xrender; } ;
struct TYPE_11__ {TYPE_2__ x11; } ;
typedef  int GLFWbool ;

/* Variables and functions */
 int GLFW_FALSE ; 
 TYPE_4__* XRenderFindVisualFormat (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_5__ _glfw ; 

GLFWbool _glfwIsVisualTransparentX11(Visual* visual)
{
    if (!_glfw.x11.xrender.available)
        return GLFW_FALSE;

    XRenderPictFormat* pf = XRenderFindVisualFormat(_glfw.x11.display, visual);
    return pf && pf->direct.alphaMask;
}