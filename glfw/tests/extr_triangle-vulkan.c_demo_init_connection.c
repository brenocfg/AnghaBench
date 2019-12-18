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
struct demo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  demo_error_callback ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gladLoadVulkanUserPtr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glad_vulkan_callback ; 
 int /*<<< orphan*/  glfwInit () ; 
 int /*<<< orphan*/  glfwSetErrorCallback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwVulkanSupported () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void demo_init_connection(struct demo *demo) {
    glfwSetErrorCallback(demo_error_callback);

    if (!glfwInit()) {
        printf("Cannot initialize GLFW.\nExiting ...\n");
        fflush(stdout);
        exit(1);
    }

    if (!glfwVulkanSupported()) {
        printf("GLFW failed to find the Vulkan loader.\nExiting ...\n");
        fflush(stdout);
        exit(1);
    }

    gladLoadVulkanUserPtr(NULL, glad_vulkan_callback, NULL);
}