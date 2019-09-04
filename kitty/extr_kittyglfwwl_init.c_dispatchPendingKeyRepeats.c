#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  id_type ;
struct TYPE_5__ {scalar_t__ keyboardFocus; int /*<<< orphan*/  keyRepeatTimer; int /*<<< orphan*/  key; } ;
struct TYPE_4__ {scalar_t__ keyboardFocus; scalar_t__ keyboardRepeatRate; TYPE_2__ keyRepeatInfo; int /*<<< orphan*/  eventLoopData; int /*<<< orphan*/  xkb; } ;
struct TYPE_6__ {TYPE_1__ wl; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_REPEAT ; 
 TYPE_3__ _glfw ; 
 int /*<<< orphan*/  changeTimerInterval (int /*<<< orphan*/ *,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  glfw_xkb_handle_key_event (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  toggleTimer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
dispatchPendingKeyRepeats(id_type timer_id, void *data) {
    if (_glfw.wl.keyRepeatInfo.keyboardFocus != _glfw.wl.keyboardFocus || _glfw.wl.keyboardRepeatRate == 0) return;
    glfw_xkb_handle_key_event(_glfw.wl.keyRepeatInfo.keyboardFocus, &_glfw.wl.xkb, _glfw.wl.keyRepeatInfo.key, GLFW_REPEAT);
    changeTimerInterval(&_glfw.wl.eventLoopData, _glfw.wl.keyRepeatInfo.keyRepeatTimer, (1.0 / (double)_glfw.wl.keyboardRepeatRate));
    toggleTimer(&_glfw.wl.eventLoopData, _glfw.wl.keyRepeatInfo.keyRepeatTimer, 1);
}