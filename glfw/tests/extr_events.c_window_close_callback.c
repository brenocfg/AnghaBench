#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int number; int /*<<< orphan*/  closeable; } ;
typedef  TYPE_1__ Slot ;
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_KEY_C ; 
 int /*<<< orphan*/  counter ; 
 char* glfwGetKeyName (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 double glfwGetTime () ; 
 TYPE_1__* glfwGetWindowUserPointer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwSetWindowShouldClose (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 

__attribute__((used)) static void window_close_callback(GLFWwindow* window)
{
    Slot* slot = glfwGetWindowUserPointer(window);
    printf("%08x to %i at %0.3f: Window close\n",
           counter++, slot->number, glfwGetTime());

    if (!slot->closeable)
    {
        printf("(( closing is disabled, press %s to re-enable )\n",
               glfwGetKeyName(GLFW_KEY_C, 0));
    }

    glfwSetWindowShouldClose(window, slot->closeable);
}