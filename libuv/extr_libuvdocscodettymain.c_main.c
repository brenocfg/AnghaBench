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
typedef  int /*<<< orphan*/  uv_write_t ;
typedef  int /*<<< orphan*/  uv_stream_t ;
struct TYPE_3__ {char* base; void* len; } ;
typedef  TYPE_1__ uv_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  UV_RUN_DEFAULT ; 
 scalar_t__ UV_TTY ; 
 int /*<<< orphan*/  UV_TTY_MODE_NORMAL ; 
 int /*<<< orphan*/  loop ; 
 void* strlen (char*) ; 
 int /*<<< orphan*/  tty ; 
 int /*<<< orphan*/  uv_default_loop () ; 
 scalar_t__ uv_guess_handle (int) ; 
 int uv_run (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_tty_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_tty_reset_mode () ; 
 int /*<<< orphan*/  uv_tty_set_mode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int,int /*<<< orphan*/ *) ; 

int main() {
    loop = uv_default_loop();

    uv_tty_init(loop, &tty, STDOUT_FILENO, 0);
    uv_tty_set_mode(&tty, UV_TTY_MODE_NORMAL);
    
    if (uv_guess_handle(1) == UV_TTY) {
        uv_write_t req;
        uv_buf_t buf;
        buf.base = "\033[41;37m";
        buf.len = strlen(buf.base);
        uv_write(&req, (uv_stream_t*) &tty, &buf, 1, NULL);
    }

    uv_write_t req;
    uv_buf_t buf;
    buf.base = "Hello TTY\n";
    buf.len = strlen(buf.base);
    uv_write(&req, (uv_stream_t*) &tty, &buf, 1, NULL);
    uv_tty_reset_mode();
    return uv_run(loop, UV_RUN_DEFAULT);
}