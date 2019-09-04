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
typedef  int /*<<< orphan*/  _GLFWwindow ;
struct TYPE_3__ {int /*<<< orphan*/  display; } ;
struct TYPE_4__ {TYPE_1__ x11; } ;
typedef  int /*<<< orphan*/  GLXFBConfig ;
typedef  int /*<<< orphan*/  GLXContext ;

/* Variables and functions */
 int /*<<< orphan*/  GLX_RGBA_TYPE ; 
 int /*<<< orphan*/  True ; 
 TYPE_2__ _glfw ; 
 int /*<<< orphan*/  glXCreateNewContext (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static GLXContext createLegacyContextGLX(_GLFWwindow* window,
                                         GLXFBConfig fbconfig,
                                         GLXContext share)
{
    return glXCreateNewContext(_glfw.x11.display,
                               fbconfig,
                               GLX_RGBA_TYPE,
                               share,
                               True);
}