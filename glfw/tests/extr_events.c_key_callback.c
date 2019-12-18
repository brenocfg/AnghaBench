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
struct TYPE_3__ {int number; int closeable; } ;
typedef  TYPE_1__ Slot ;
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
#define  GLFW_KEY_C 129 
#define  GLFW_KEY_L 128 
 int /*<<< orphan*/  GLFW_LOCK_KEY_MODS ; 
 int GLFW_PRESS ; 
 int /*<<< orphan*/  counter ; 
 char* get_action_name (int) ; 
 char* get_key_name (int) ; 
 char* get_mods_name (int) ; 
 int glfwGetInputMode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* glfwGetKeyName (int,int) ; 
 double glfwGetTime () ; 
 TYPE_1__* glfwGetWindowUserPointer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwSetInputMode (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 

__attribute__((used)) static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Slot* slot = glfwGetWindowUserPointer(window);
    const char* name = glfwGetKeyName(key, scancode);

    if (name)
    {
        printf("%08x to %i at %0.3f: Key 0x%04x Scancode 0x%04x (%s) (%s) (with%s) was %s\n",
               counter++, slot->number, glfwGetTime(), key, scancode,
               get_key_name(key),
               name,
               get_mods_name(mods),
               get_action_name(action));
    }
    else
    {
        printf("%08x to %i at %0.3f: Key 0x%04x Scancode 0x%04x (%s) (with%s) was %s\n",
               counter++, slot->number, glfwGetTime(), key, scancode,
               get_key_name(key),
               get_mods_name(mods),
               get_action_name(action));
    }

    if (action != GLFW_PRESS)
        return;

    switch (key)
    {
        case GLFW_KEY_C:
        {
            slot->closeable = !slot->closeable;

            printf("(( closing %s ))\n", slot->closeable ? "enabled" : "disabled");
            break;
        }

        case GLFW_KEY_L:
        {
            const int state = glfwGetInputMode(window, GLFW_LOCK_KEY_MODS);
            glfwSetInputMode(window, GLFW_LOCK_KEY_MODS, !state);

            printf("(( lock key mods %s ))\n", !state ? "enabled" : "disabled");
            break;
        }
    }
}