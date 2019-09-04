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
typedef  int xkb_mod_mask_t ;
struct xkb_state {int dummy; } ;
struct TYPE_3__ {int* unknownModifiers; } ;
typedef  TYPE_1__ _GLFWXKBData ;

/* Variables and functions */
 int XKB_MOD_INVALID ; 
 int /*<<< orphan*/  XKB_STATE_MODS_EFFECTIVE ; 
 scalar_t__ xkb_state_mod_index_is_active (struct xkb_state*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline xkb_mod_mask_t
active_unknown_modifiers(_GLFWXKBData *xkb, struct xkb_state *state) {
    size_t i = 0;
    xkb_mod_mask_t ans = 0;
    while (xkb->unknownModifiers[i] != XKB_MOD_INVALID) {
        if (xkb_state_mod_index_is_active(state, xkb->unknownModifiers[i], XKB_STATE_MODS_EFFECTIVE)) ans |= (1 << xkb->unknownModifiers[i]);
        i++;
    }
    return ans;
}