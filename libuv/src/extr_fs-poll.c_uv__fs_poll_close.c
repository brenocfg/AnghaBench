#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uv_handle_t ;
struct TYPE_4__ {int /*<<< orphan*/ * poll_ctx; } ;
typedef  TYPE_1__ uv_fs_poll_t ;

/* Variables and functions */
 int /*<<< orphan*/  uv__make_close_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_fs_poll_stop (TYPE_1__*) ; 

void uv__fs_poll_close(uv_fs_poll_t* handle) {
  uv_fs_poll_stop(handle);

  if (handle->poll_ctx == NULL)
    uv__make_close_pending((uv_handle_t*)handle);
}