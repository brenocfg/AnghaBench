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

/* Variables and functions */
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  UV_RUN_DEFAULT ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int height ; 
 int /*<<< orphan*/  loop ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  tick ; 
 int /*<<< orphan*/  tty ; 
 int /*<<< orphan*/  update ; 
 int /*<<< orphan*/  uv_default_loop () ; 
 int uv_run (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_timer_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_timer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ uv_tty_get_winsize (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  uv_tty_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_tty_reset_mode () ; 
 int /*<<< orphan*/  uv_tty_set_mode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int width ; 

int main() {
    loop = uv_default_loop();

    uv_tty_init(loop, &tty, STDOUT_FILENO, 0);
    uv_tty_set_mode(&tty, 0);
    
    if (uv_tty_get_winsize(&tty, &width, &height)) {
        fprintf(stderr, "Could not get TTY information\n");
        uv_tty_reset_mode();
        return 1;
    }

    fprintf(stderr, "Width %d, height %d\n", width, height);
    uv_timer_init(loop, &tick);
    uv_timer_start(&tick, update, 200, 200);
    return uv_run(loop, UV_RUN_DEFAULT);
}