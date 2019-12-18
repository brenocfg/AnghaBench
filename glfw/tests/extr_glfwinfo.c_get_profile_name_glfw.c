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
 int GLFW_OPENGL_COMPAT_PROFILE ; 
 int GLFW_OPENGL_CORE_PROFILE ; 
 char const* PROFILE_NAME_COMPAT ; 
 char const* PROFILE_NAME_CORE ; 

__attribute__((used)) static const char* get_profile_name_glfw(int profile)
{
    if (profile == GLFW_OPENGL_COMPAT_PROFILE)
        return PROFILE_NAME_COMPAT;
    if (profile == GLFW_OPENGL_CORE_PROFILE)
        return PROFILE_NAME_CORE;

    return "unknown";
}