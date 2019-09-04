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
struct TYPE_8__ {int /*<<< orphan*/  mouse_tracking_protocol; int /*<<< orphan*/  mouse_tracking_mode; } ;
struct TYPE_10__ {TYPE_1__ modes; int /*<<< orphan*/  modes_savepoints; } ;
struct TYPE_9__ {int /*<<< orphan*/  mouse_tracking_protocol; int /*<<< orphan*/  mouse_tracking_mode; int /*<<< orphan*/  mEXTENDED_KEYBOARD; int /*<<< orphan*/  mFOCUS_TRACKING; int /*<<< orphan*/  mBRACKETED_PASTE; int /*<<< orphan*/  mDECCKM; int /*<<< orphan*/  mDECARM; int /*<<< orphan*/  mDECAWM; int /*<<< orphan*/  mDECOM; int /*<<< orphan*/  mDECSCNM; int /*<<< orphan*/  mDECTCEM; } ;
typedef  TYPE_2__ ScreenModes ;
typedef  TYPE_3__ Screen ;

/* Variables and functions */
 int /*<<< orphan*/  BRACKETED_PASTE ; 
 int /*<<< orphan*/  DECARM ; 
 int /*<<< orphan*/  DECAWM ; 
 int /*<<< orphan*/  DECCKM ; 
 int /*<<< orphan*/  DECOM ; 
 int /*<<< orphan*/  DECSCNM ; 
 int /*<<< orphan*/  DECTCEM ; 
 int /*<<< orphan*/  EXTENDED_KEYBOARD ; 
 int /*<<< orphan*/  FOCUS_TRACKING ; 
 int /*<<< orphan*/  buffer_pop (int /*<<< orphan*/ *,TYPE_2__ const*) ; 
 TYPE_2__ empty_modes ; 
 int /*<<< orphan*/  set_mode_from_const (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
screen_restore_modes(Screen *self) {
    const ScreenModes *m;
    buffer_pop(&self->modes_savepoints, m);
    if (m == NULL) m = &empty_modes;
#define S(name) set_mode_from_const(self, name, m->m##name)
    S(DECTCEM); S(DECSCNM); S(DECSCNM); S(DECOM); S(DECAWM); S(DECARM); S(DECCKM);
    S(BRACKETED_PASTE); S(FOCUS_TRACKING); S(EXTENDED_KEYBOARD);
    self->modes.mouse_tracking_mode = m->mouse_tracking_mode;
    self->modes.mouse_tracking_protocol = m->mouse_tracking_protocol;
#undef S
}