#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ allocated; scalar_t__ index; } ;
struct TYPE_5__ {TYPE_1__ win32; } ;
typedef  TYPE_2__ _GLFWtls ;
typedef  scalar_t__ GLFWbool ;

/* Variables and functions */
 scalar_t__ GLFW_FALSE ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 scalar_t__ GLFW_TRUE ; 
 scalar_t__ TLS_OUT_OF_INDEXES ; 
 scalar_t__ TlsAlloc () ; 
 int /*<<< orphan*/  _glfwInputErrorWin32 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  assert (int) ; 

GLFWbool _glfwPlatformCreateTls(_GLFWtls* tls)
{
    assert(tls->win32.allocated == GLFW_FALSE);

    tls->win32.index = TlsAlloc();
    if (tls->win32.index == TLS_OUT_OF_INDEXES)
    {
        _glfwInputErrorWin32(GLFW_PLATFORM_ERROR,
                             "Win32: Failed to allocate TLS index");
        return GLFW_FALSE;
    }

    tls->win32.allocated = GLFW_TRUE;
    return GLFW_TRUE;
}