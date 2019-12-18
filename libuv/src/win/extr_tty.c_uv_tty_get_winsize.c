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
struct TYPE_3__ {int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ uv_tty_t ;
typedef  int /*<<< orphan*/  CONSOLE_SCREEN_BUFFER_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  GetConsoleScreenBufferInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  uv_sem_post (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_sem_wait (int /*<<< orphan*/ *) ; 
 int uv_translate_sys_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_tty_output_lock ; 
 int /*<<< orphan*/  uv_tty_update_virtual_window (int /*<<< orphan*/ *) ; 
 int uv_tty_virtual_height ; 
 int uv_tty_virtual_width ; 

int uv_tty_get_winsize(uv_tty_t* tty, int* width, int* height) {
  CONSOLE_SCREEN_BUFFER_INFO info;

  if (!GetConsoleScreenBufferInfo(tty->handle, &info)) {
    return uv_translate_sys_error(GetLastError());
  }

  uv_sem_wait(&uv_tty_output_lock);
  uv_tty_update_virtual_window(&info);
  uv_sem_post(&uv_tty_output_lock);

  *width = uv_tty_virtual_width;
  *height = uv_tty_virtual_height;

  return 0;
}