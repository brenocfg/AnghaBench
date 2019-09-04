#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int has_pending_resizes; size_t num_os_windows; TYPE_1__* os_windows; } ;
struct TYPE_6__ {double last_resize_event_at; int num_of_resize_events; int /*<<< orphan*/  member_0; scalar_t__ os_says_resize_complete; scalar_t__ from_os_notification; scalar_t__ in_progress; } ;
struct TYPE_5__ {TYPE_2__ live_resize; } ;
typedef  TYPE_1__ OSWindow ;
typedef  TYPE_2__ LiveResizeInfo ;

/* Variables and functions */
 double MAX (double,double) ; 
 double OPT (int /*<<< orphan*/ ) ; 
 TYPE_4__ global_state ; 
 int /*<<< orphan*/  resize_debounce_time ; 
 int /*<<< orphan*/  set_maximum_wait (double) ; 
 int /*<<< orphan*/  update_os_window_viewport (TYPE_1__*,int) ; 

__attribute__((used)) static inline void
process_pending_resizes(double now) {
    global_state.has_pending_resizes = false;
    for (size_t i = 0; i < global_state.num_os_windows; i++) {
        OSWindow *w = global_state.os_windows + i;
        if (w->live_resize.in_progress) {
            bool update_viewport = false;
            if (w->live_resize.from_os_notification) {
                if (w->live_resize.os_says_resize_complete || (now - w->live_resize.last_resize_event_at) > 1) update_viewport = true;
            } else {
                double debounce_time = OPT(resize_debounce_time);
                // if more than one resize event has occurred, wait at least 0.2 secs
                // before repainting, to avoid rapid transitions between the cells banner
                // and the normal screen
                if (w->live_resize.num_of_resize_events > 1) debounce_time = MAX(0.2, debounce_time);
                if (now - w->live_resize.last_resize_event_at >= debounce_time) update_viewport = true;
                else {
                    global_state.has_pending_resizes = true;
                    set_maximum_wait(OPT(resize_debounce_time) - now + w->live_resize.last_resize_event_at);
                }
            }
            if (update_viewport) {
                static const LiveResizeInfo empty = {0};
                update_os_window_viewport(w, true);
                w->live_resize = empty;
            }
        }
    }
}