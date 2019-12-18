#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int state; int detail; } ;
typedef  TYPE_1__ xcb_key_press_event_t ;
struct TYPE_5__ {scalar_t__ response_type; } ;
typedef  TYPE_2__ xcb_generic_event_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  input_type_t ;
typedef  int i3_event_state_mask_t ;
typedef  int /*<<< orphan*/  Binding ;

/* Variables and functions */
 int /*<<< orphan*/  B_KEYBOARD ; 
 int /*<<< orphan*/  B_MOUSE ; 
 int /*<<< orphan*/  DLOG (char*,int) ; 
 int I3_XKB_GROUP_MASK_1 ; 
 int I3_XKB_GROUP_MASK_2 ; 
 int I3_XKB_GROUP_MASK_3 ; 
 int I3_XKB_GROUP_MASK_4 ; 
 scalar_t__ XCB_BUTTON_PRESS ; 
 scalar_t__ XCB_BUTTON_RELEASE ; 
 scalar_t__ XCB_KEY_RELEASE ; 
 int const XCB_MOD_MASK_LOCK ; 
#define  XCB_XKB_GROUP_1 131 
#define  XCB_XKB_GROUP_2 130 
#define  XCB_XKB_GROUP_3 129 
#define  XCB_XKB_GROUP_4 128 
 int /*<<< orphan*/ * get_binding (int,int const,int const,int /*<<< orphan*/  const) ; 

Binding *get_binding_from_xcb_event(xcb_generic_event_t *event) {
    const bool is_release = (event->response_type == XCB_KEY_RELEASE ||
                             event->response_type == XCB_BUTTON_RELEASE);

    const input_type_t input_type = ((event->response_type == XCB_BUTTON_RELEASE ||
                                      event->response_type == XCB_BUTTON_PRESS)
                                         ? B_MOUSE
                                         : B_KEYBOARD);

    const uint16_t event_state = ((xcb_key_press_event_t *)event)->state;
    const uint16_t event_detail = ((xcb_key_press_event_t *)event)->detail;

    /* Remove the CapsLock bit */
    i3_event_state_mask_t state_filtered = event_state & ~XCB_MOD_MASK_LOCK;
    DLOG("(removed capslock, state = 0x%x)\n", state_filtered);
    /* Transform the keyboard_group from bit 13 and bit 14 into an
     * i3_xkb_group_mask_t, so that get_binding() can just bitwise AND the
     * configured bindings against |state_filtered|.
     *
     * These bits are only set because we set the XKB client flags
     * XCB_XKB_PER_CLIENT_FLAG_GRABS_USE_XKB_STATE and
     * XCB_XKB_PER_CLIENT_FLAG_LOOKUP_STATE_WHEN_GRABBED. See also doc/kbproto
     * section 2.2.2:
     * https://www.x.org/releases/X11R7.7/doc/kbproto/xkbproto.html#Computing_A_State_Field_from_an_XKB_State */
    switch ((event_state & 0x6000) >> 13) {
        case XCB_XKB_GROUP_1:
            state_filtered |= (I3_XKB_GROUP_MASK_1 << 16);
            break;
        case XCB_XKB_GROUP_2:
            state_filtered |= (I3_XKB_GROUP_MASK_2 << 16);
            break;
        case XCB_XKB_GROUP_3:
            state_filtered |= (I3_XKB_GROUP_MASK_3 << 16);
            break;
        case XCB_XKB_GROUP_4:
            state_filtered |= (I3_XKB_GROUP_MASK_4 << 16);
            break;
    }
    state_filtered &= ~0x6000;
    DLOG("(transformed keyboard group, state = 0x%x)\n", state_filtered);
    return get_binding(state_filtered, is_release, event_detail, input_type);
}