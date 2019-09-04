#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  dump_callback; } ;
struct TYPE_7__ {double wait_time; scalar_t__ activated_at; scalar_t__ used; } ;
struct TYPE_8__ {scalar_t__ read_buf_sz; double new_input_at; TYPE_1__ pending_mode; } ;
typedef  TYPE_2__ Screen ;
typedef  TYPE_3__ ChildMonitor ;

/* Variables and functions */
 double MAX (int /*<<< orphan*/ ,scalar_t__) ; 
 double OPT (int /*<<< orphan*/ ) ; 
 scalar_t__ READ_BUF_SZ ; 
 int /*<<< orphan*/  input_delay ; 
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  parse_func (TYPE_2__*,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  read ; 
 int /*<<< orphan*/  screen_mutex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_maximum_wait (double) ; 
 int /*<<< orphan*/  unlock ; 
 int /*<<< orphan*/  wakeup_io_loop (int) ; 

__attribute__((used)) static inline void
do_parse(ChildMonitor *self, Screen *screen, double now) {
    screen_mutex(lock, read);
    if (screen->read_buf_sz || screen->pending_mode.used) {
        double time_since_new_input = now - screen->new_input_at;
        if (time_since_new_input >= OPT(input_delay)) {
            bool read_buf_full = screen->read_buf_sz >= READ_BUF_SZ;
            parse_func(screen, self->dump_callback, now);
            if (read_buf_full) wakeup_io_loop(false);  // Ensure the read fd has POLLIN set
            screen->new_input_at = 0;
            if (screen->pending_mode.activated_at) {
                double time_since_pending = MAX(0, now - screen->pending_mode.activated_at);
                set_maximum_wait(screen->pending_mode.wait_time - time_since_pending);
            }
        } else set_maximum_wait(OPT(input_delay) - time_since_new_input);
    }
    screen_mutex(unlock, read);
}