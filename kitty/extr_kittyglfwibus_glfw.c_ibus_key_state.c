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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 unsigned int GLFW_MOD_ALT ; 
 unsigned int GLFW_MOD_CAPS_LOCK ; 
 unsigned int GLFW_MOD_CONTROL ; 
 unsigned int GLFW_MOD_NUM_LOCK ; 
 unsigned int GLFW_MOD_SHIFT ; 
 unsigned int GLFW_MOD_SUPER ; 
 int GLFW_RELEASE ; 
 int /*<<< orphan*/  IBUS_CONTROL_MASK ; 
 int /*<<< orphan*/  IBUS_LOCK_MASK ; 
 int /*<<< orphan*/  IBUS_MOD1_MASK ; 
 int /*<<< orphan*/  IBUS_MOD2_MASK ; 
 int /*<<< orphan*/  IBUS_MOD4_MASK ; 
 int /*<<< orphan*/  IBUS_RELEASE_MASK ; 
 int /*<<< orphan*/  IBUS_SHIFT_MASK ; 

__attribute__((used)) static inline uint32_t
ibus_key_state(unsigned int glfw_modifiers, int action) {
    uint32_t ans = action == GLFW_RELEASE ? IBUS_RELEASE_MASK : 0;
#define M(g, i) if(glfw_modifiers & GLFW_MOD_##g) ans |= i
    M(SHIFT, IBUS_SHIFT_MASK);
    M(CAPS_LOCK, IBUS_LOCK_MASK);
    M(CONTROL, IBUS_CONTROL_MASK);
    M(ALT, IBUS_MOD1_MASK);
    M(NUM_LOCK, IBUS_MOD2_MASK);
    M(SUPER, IBUS_MOD4_MASK);
#undef M
    return ans;
}