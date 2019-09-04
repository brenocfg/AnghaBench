#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int mLNM; int mIRM; int mDECARM; int mBRACKETED_PASTE; int mEXTENDED_KEYBOARD; int mFOCUS_TRACKING; int mDECCKM; int mDECTCEM; int mDECSCNM; int mDECOM; int mDECAWM; int mDECCOLM; int /*<<< orphan*/  mouse_tracking_protocol; int /*<<< orphan*/  mouse_tracking_mode; } ;
struct TYPE_10__ {int is_dirty; int /*<<< orphan*/  main_linebuf; int /*<<< orphan*/  linebuf; TYPE_2__* cursor; TYPE_1__ modes; } ;
struct TYPE_9__ {int blink; } ;
typedef  TYPE_3__ Screen ;

/* Variables and functions */
#define  ALTERNATE_SCREEN 149 
 int /*<<< orphan*/  ANY_MODE ; 
#define  BRACKETED_PASTE 148 
 int /*<<< orphan*/  BUTTON_MODE ; 
#define  CONTROL_CURSOR_BLINK 147 
#define  DECARM 146 
#define  DECAWM 145 
#define  DECCKM 144 
#define  DECCOLM 143 
#define  DECNRCM 142 
#define  DECOM 141 
#define  DECSCLM 140 
#define  DECSCNM 139 
#define  DECTCEM 138 
 int /*<<< orphan*/  ERROR_PREFIX ; 
#define  EXTENDED_KEYBOARD 137 
#define  FOCUS_TRACKING 136 
#define  IRM 135 
#define  LNM 134 
 int /*<<< orphan*/  MOTION_MODE ; 
#define  MOUSE_BUTTON_TRACKING 133 
#define  MOUSE_MOTION_TRACKING 132 
#define  MOUSE_MOVE_TRACKING 131 
#define  MOUSE_SGR_MODE 130 
#define  MOUSE_URXVT_MODE 129 
#define  MOUSE_UTF8_MODE 128 
 int /*<<< orphan*/  SGR_PROTOCOL ; 
 int /*<<< orphan*/  URXVT_PROTOCOL ; 
 int /*<<< orphan*/  UTF8_PROTOCOL ; 
 int /*<<< orphan*/  log_error (char*,int /*<<< orphan*/ ,char*,unsigned int,char*) ; 
 int /*<<< orphan*/  screen_cursor_position (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  screen_erase_in_display (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  screen_toggle_screen_buffer (TYPE_3__*) ; 

__attribute__((used)) static inline void
set_mode_from_const(Screen *self, unsigned int mode, bool val) {
#define SIMPLE_MODE(name) \
    case name: \
        self->modes.m##name = val; break;

#define MOUSE_MODE(name, attr, value) \
    case name: \
        self->modes.attr = val ? value : 0; break;

    bool private;
    switch(mode) {
        SIMPLE_MODE(LNM)
        SIMPLE_MODE(IRM)
        SIMPLE_MODE(DECARM)
        SIMPLE_MODE(BRACKETED_PASTE)
        SIMPLE_MODE(EXTENDED_KEYBOARD)
        SIMPLE_MODE(FOCUS_TRACKING)
        MOUSE_MODE(MOUSE_BUTTON_TRACKING, mouse_tracking_mode, BUTTON_MODE)
        MOUSE_MODE(MOUSE_MOTION_TRACKING, mouse_tracking_mode, MOTION_MODE)
        MOUSE_MODE(MOUSE_MOVE_TRACKING, mouse_tracking_mode, ANY_MODE)
        MOUSE_MODE(MOUSE_UTF8_MODE, mouse_tracking_protocol, UTF8_PROTOCOL)
        MOUSE_MODE(MOUSE_SGR_MODE, mouse_tracking_protocol, SGR_PROTOCOL)
        MOUSE_MODE(MOUSE_URXVT_MODE, mouse_tracking_protocol, URXVT_PROTOCOL)

        case DECSCLM:
        case DECNRCM:
            break;  // we ignore these modes
        case DECCKM:
            self->modes.mDECCKM = val;
            break;
        case DECTCEM:
            self->modes.mDECTCEM = val;
            break;
        case DECSCNM:
            // Render screen in reverse video
            if (self->modes.mDECSCNM != val) {
                self->modes.mDECSCNM = val;
                self->is_dirty = true;
            }
            break;
        case DECOM:
            self->modes.mDECOM = val;
            // According to `vttest`, DECOM should also home the cursor, see
            // vttest/main.c:303.
            screen_cursor_position(self, 1, 1);
            break;
        case DECAWM:
            self->modes.mDECAWM = val; break;
        case DECCOLM:
            self->modes.mDECCOLM = val;
            if (val) {
                // When DECCOLM mode is set, the screen is erased and the cursor
                // moves to the home position.
                screen_erase_in_display(self, 2, false);
                screen_cursor_position(self, 1, 1);
            }
            break;
        case CONTROL_CURSOR_BLINK:
            self->cursor->blink = val;
            break;
        case ALTERNATE_SCREEN:
            if (val && self->linebuf == self->main_linebuf) screen_toggle_screen_buffer(self);
            else if (!val && self->linebuf != self->main_linebuf) screen_toggle_screen_buffer(self);
            break;
        default:
            private = mode >= 1 << 5;
            if (private) mode >>= 5;
            log_error("%s %s %u %s", ERROR_PREFIX, "Unsupported screen mode: ", mode, private ? "(private)" : "");
    }
#undef SIMPLE_MODE
#undef MOUSE_MODE
}