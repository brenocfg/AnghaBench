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
struct TYPE_4__ {scalar_t__ allocated; int /*<<< orphan*/  key; } ;
struct TYPE_5__ {TYPE_1__ posix; } ;
typedef  TYPE_2__ _GLFWtls ;
typedef  scalar_t__ GLFWbool ;

/* Variables and functions */
 scalar_t__ GLFW_FALSE ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 scalar_t__ GLFW_TRUE ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ pthread_key_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

GLFWbool _glfwPlatformCreateTls(_GLFWtls* tls)
{
    assert(tls->posix.allocated == GLFW_FALSE);

    if (pthread_key_create(&tls->posix.key, NULL) != 0)
    {
        _glfwInputError(GLFW_PLATFORM_ERROR,
                        "POSIX: Failed to create context TLS");
        return GLFW_FALSE;
    }

    tls->posix.allocated = GLFW_TRUE;
    return GLFW_TRUE;
}