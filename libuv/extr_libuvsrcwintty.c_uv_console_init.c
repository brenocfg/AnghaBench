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
 scalar_t__ CreateFileW (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FILE_SHARE_WRITE ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  QueueUserWorkItem (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WT_EXECUTELONGFUNCTION ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ uv__tty_console_handle ; 
 int /*<<< orphan*/  uv__tty_console_resize_message_loop_thread ; 
 scalar_t__ uv_sem_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  uv_tty_output_lock ; 

void uv_console_init(void) {
  if (uv_sem_init(&uv_tty_output_lock, 1))
    abort();
  uv__tty_console_handle = CreateFileW(L"CONOUT$",
                                       GENERIC_READ | GENERIC_WRITE,
                                       FILE_SHARE_WRITE,
                                       0,
                                       OPEN_EXISTING,
                                       0,
                                       0);
  if (uv__tty_console_handle != INVALID_HANDLE_VALUE) {
    QueueUserWorkItem(uv__tty_console_resize_message_loop_thread,
                      NULL,
                      WT_EXECUTELONGFUNCTION);
  }
}