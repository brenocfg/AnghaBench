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
 int UV_CHANGE ; 
 int /*<<< orphan*/  close_cb ; 
 int /*<<< orphan*/  fs_event ; 
 int /*<<< orphan*/  fs_event_cb_called ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  uv_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ uv_fs_event_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fs_event_cb_file(uv_fs_event_t* handle, const char* filename,
  int events, int status) {
  ++fs_event_cb_called;
  ASSERT(handle == &fs_event);
  ASSERT(status == 0);
  ASSERT(events == UV_CHANGE);
  #if defined(__APPLE__) || defined(_WIN32) || defined(__linux__)
  ASSERT(strcmp(filename, "file2") == 0);
  #else
  ASSERT(filename == NULL || strcmp(filename, "file2") == 0);
  #endif
  ASSERT(0 == uv_fs_event_stop(handle));
  uv_close((uv_handle_t*)handle, close_cb);
}