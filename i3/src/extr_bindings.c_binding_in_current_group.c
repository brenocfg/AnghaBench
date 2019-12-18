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
struct TYPE_3__ {int event_state_mask; } ;
typedef  TYPE_1__ Binding ;

/* Variables and functions */
 int /*<<< orphan*/  ELOG (char*,int) ; 
 int I3_XKB_GROUP_MASK_1 ; 
 int I3_XKB_GROUP_MASK_2 ; 
 int I3_XKB_GROUP_MASK_3 ; 
 int I3_XKB_GROUP_MASK_4 ; 
 int I3_XKB_GROUP_MASK_ANY ; 
#define  XCB_XKB_GROUP_1 131 
#define  XCB_XKB_GROUP_2 130 
#define  XCB_XKB_GROUP_3 129 
#define  XCB_XKB_GROUP_4 128 
 int xkb_current_group ; 

__attribute__((used)) static bool binding_in_current_group(const Binding *bind) {
    /* If no bits are set, the binding should be installed in every group. */
    if ((bind->event_state_mask >> 16) == I3_XKB_GROUP_MASK_ANY)
        return true;
    switch (xkb_current_group) {
        case XCB_XKB_GROUP_1:
            return ((bind->event_state_mask >> 16) & I3_XKB_GROUP_MASK_1);
        case XCB_XKB_GROUP_2:
            return ((bind->event_state_mask >> 16) & I3_XKB_GROUP_MASK_2);
        case XCB_XKB_GROUP_3:
            return ((bind->event_state_mask >> 16) & I3_XKB_GROUP_MASK_3);
        case XCB_XKB_GROUP_4:
            return ((bind->event_state_mask >> 16) & I3_XKB_GROUP_MASK_4);
        default:
            ELOG("BUG: xkb_current_group (= %d) outside of [XCB_XKB_GROUP_1..XCB_XKB_GROUP_4]\n", xkb_current_group);
            return false;
    }
}