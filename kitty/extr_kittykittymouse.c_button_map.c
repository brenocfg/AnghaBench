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
 unsigned int EXTRA_BUTTON_INDICATOR ; 
#define  GLFW_MOUSE_BUTTON_4 132 
#define  GLFW_MOUSE_BUTTON_5 131 
#define  GLFW_MOUSE_BUTTON_LEFT 130 
#define  GLFW_MOUSE_BUTTON_MIDDLE 129 
#define  GLFW_MOUSE_BUTTON_RIGHT 128 
 unsigned int UINT_MAX ; 

__attribute__((used)) static inline unsigned int
button_map(int button) {
    switch(button) {
        case GLFW_MOUSE_BUTTON_LEFT:
            return 0;
        case GLFW_MOUSE_BUTTON_RIGHT:
            return 2;
        case GLFW_MOUSE_BUTTON_MIDDLE:
            return 1;
        case GLFW_MOUSE_BUTTON_4:
            return EXTRA_BUTTON_INDICATOR;
        case GLFW_MOUSE_BUTTON_5:
            return EXTRA_BUTTON_INDICATOR | 1;
        default:
            return UINT_MAX;
    }
}