#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  VkInstance ;
typedef  int /*<<< orphan*/  GLADapiproc ;

/* Variables and functions */
 int /*<<< orphan*/  glfwGetInstanceProcAddress (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static GLADapiproc glad_vulkan_callback(const char* name, void* user)
{
    return glfwGetInstanceProcAddress((VkInstance) user, name);
}