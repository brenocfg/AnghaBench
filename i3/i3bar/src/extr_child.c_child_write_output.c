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
typedef  int ssize_t ;
struct TYPE_2__ {int click_events; } ;

/* Variables and functions */
 TYPE_1__ child ; 
 int /*<<< orphan*/  child_stdin ; 
 int /*<<< orphan*/  draw_bars (int) ; 
 int /*<<< orphan*/  gen ; 
 int /*<<< orphan*/  kill_child () ; 
 int /*<<< orphan*/  set_statusline_error (char*) ; 
 int writeall (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  yajl_gen_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yajl_gen_get_buf (int /*<<< orphan*/ ,unsigned char const**,size_t*) ; 

__attribute__((used)) static void child_write_output(void) {
    if (child.click_events) {
        const unsigned char *output;
        size_t size;
        ssize_t n;

        yajl_gen_get_buf(gen, &output, &size);

        n = writeall(child_stdin, output, size);
        if (n != -1)
            n = writeall(child_stdin, "\n", 1);

        yajl_gen_clear(gen);

        if (n == -1) {
            child.click_events = false;
            kill_child();
            set_statusline_error("child_write_output failed");
            draw_bars(false);
        }
    }
}