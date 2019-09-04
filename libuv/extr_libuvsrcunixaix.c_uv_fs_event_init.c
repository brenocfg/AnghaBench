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
typedef  int /*<<< orphan*/  uv_loop_t ;
typedef  int /*<<< orphan*/  uv_fs_event_t ;

/* Variables and functions */
 int UV_ENOSYS ; 

int uv_fs_event_init(uv_loop_t* loop, uv_fs_event_t* handle) {
#ifdef HAVE_SYS_AHAFS_EVPRODS_H
  uv__handle_init(loop, (uv_handle_t*)handle, UV_FS_EVENT);
  return 0;
#else
  return UV_ENOSYS;
#endif
}