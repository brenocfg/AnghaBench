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
typedef  int /*<<< orphan*/  uv_handle_t ;
typedef  int /*<<< orphan*/  uv_fs_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  close_cb ; 
 int fs_event_cb_called ; 
 int /*<<< orphan*/  uv_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fs_event_cb_close(uv_fs_event_t* handle,
                              const char* filename,
                              int events,
                              int status) {
  ASSERT(status == 0);

  ASSERT(fs_event_cb_called < 3);
  ++fs_event_cb_called;

  if (fs_event_cb_called == 3) {
    uv_close((uv_handle_t*) handle, close_cb);
  }
}