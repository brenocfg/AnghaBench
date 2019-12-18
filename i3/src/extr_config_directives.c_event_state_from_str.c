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
typedef  int i3_event_state_mask_t ;

/* Variables and functions */
 int I3_XKB_GROUP_MASK_1 ; 
 int I3_XKB_GROUP_MASK_2 ; 
 int I3_XKB_GROUP_MASK_3 ; 
 int I3_XKB_GROUP_MASK_4 ; 
 int XCB_KEY_BUT_MASK_CONTROL ; 
 int XCB_KEY_BUT_MASK_MOD_1 ; 
 int XCB_KEY_BUT_MASK_MOD_2 ; 
 int XCB_KEY_BUT_MASK_MOD_3 ; 
 int XCB_KEY_BUT_MASK_MOD_4 ; 
 int XCB_KEY_BUT_MASK_MOD_5 ; 
 int XCB_KEY_BUT_MASK_SHIFT ; 
 int /*<<< orphan*/ * strstr (char const*,char*) ; 

i3_event_state_mask_t event_state_from_str(const char *str) {
    /* It might be better to use strtok() here, but the simpler strstr() should
     * do for now. */
    i3_event_state_mask_t result = 0;
    if (str == NULL)
        return result;
    if (strstr(str, "Mod1") != NULL)
        result |= XCB_KEY_BUT_MASK_MOD_1;
    if (strstr(str, "Mod2") != NULL)
        result |= XCB_KEY_BUT_MASK_MOD_2;
    if (strstr(str, "Mod3") != NULL)
        result |= XCB_KEY_BUT_MASK_MOD_3;
    if (strstr(str, "Mod4") != NULL)
        result |= XCB_KEY_BUT_MASK_MOD_4;
    if (strstr(str, "Mod5") != NULL)
        result |= XCB_KEY_BUT_MASK_MOD_5;
    if (strstr(str, "Control") != NULL ||
        strstr(str, "Ctrl") != NULL)
        result |= XCB_KEY_BUT_MASK_CONTROL;
    if (strstr(str, "Shift") != NULL)
        result |= XCB_KEY_BUT_MASK_SHIFT;

    if (strstr(str, "Group1") != NULL)
        result |= (I3_XKB_GROUP_MASK_1 << 16);
    if (strstr(str, "Group2") != NULL ||
        strstr(str, "Mode_switch") != NULL)
        result |= (I3_XKB_GROUP_MASK_2 << 16);
    if (strstr(str, "Group3") != NULL)
        result |= (I3_XKB_GROUP_MASK_3 << 16);
    if (strstr(str, "Group4") != NULL)
        result |= (I3_XKB_GROUP_MASK_4 << 16);
    return result;
}