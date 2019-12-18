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

/* Variables and functions */
 int GLFW_MOD_ALT ; 
 int GLFW_MOD_CAPS_LOCK ; 
 int GLFW_MOD_CONTROL ; 
 int GLFW_MOD_NUM_LOCK ; 
 int GLFW_MOD_SHIFT ; 
 int GLFW_MOD_SUPER ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 

__attribute__((used)) static const char* get_mods_name(int mods)
{
    static char name[512];

    if (mods == 0)
        return " no mods";

    name[0] = '\0';

    if (mods & GLFW_MOD_SHIFT)
        strcat(name, " shift");
    if (mods & GLFW_MOD_CONTROL)
        strcat(name, " control");
    if (mods & GLFW_MOD_ALT)
        strcat(name, " alt");
    if (mods & GLFW_MOD_SUPER)
        strcat(name, " super");
    if (mods & GLFW_MOD_CAPS_LOCK)
        strcat(name, " capslock-on");
    if (mods & GLFW_MOD_NUM_LOCK)
        strcat(name, " numlock-on");

    return name;
}