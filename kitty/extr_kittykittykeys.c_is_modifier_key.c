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
#define  GLFW_KEY_LEFT_ALT 135 
#define  GLFW_KEY_LEFT_CONTROL 134 
#define  GLFW_KEY_LEFT_SHIFT 133 
#define  GLFW_KEY_LEFT_SUPER 132 
#define  GLFW_KEY_RIGHT_ALT 131 
#define  GLFW_KEY_RIGHT_CONTROL 130 
#define  GLFW_KEY_RIGHT_SHIFT 129 
#define  GLFW_KEY_RIGHT_SUPER 128 

__attribute__((used)) static inline bool
is_modifier_key(int key) {
    switch(key) {
        case GLFW_KEY_LEFT_SHIFT:
        case GLFW_KEY_RIGHT_SHIFT:
        case GLFW_KEY_LEFT_ALT:
        case GLFW_KEY_RIGHT_ALT:
        case GLFW_KEY_LEFT_CONTROL:
        case GLFW_KEY_RIGHT_CONTROL:
        case GLFW_KEY_LEFT_SUPER:
        case GLFW_KEY_RIGHT_SUPER:
            return true;
        default:
            return false;
    }
}