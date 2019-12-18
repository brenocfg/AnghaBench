#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ev_loop {int dummy; } ;
typedef  int /*<<< orphan*/  ev_io ;
struct TYPE_2__ {scalar_t__ version; } ;

/* Variables and functions */
 TYPE_1__ child ; 
 int /*<<< orphan*/  draw_bars (int) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 unsigned char* get_buffer (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  read_flat_input (char*,int) ; 
 int read_json_input (unsigned char*,int) ; 

__attribute__((used)) static void stdin_io_cb(struct ev_loop *loop, ev_io *watcher, int revents) {
    int rec;
    unsigned char *buffer = get_buffer(watcher, &rec);
    if (buffer == NULL)
        return;
    bool has_urgent = false;
    if (child.version > 0) {
        has_urgent = read_json_input(buffer, rec);
    } else {
        read_flat_input((char *)buffer, rec);
    }
    free(buffer);
    draw_bars(has_urgent);
}