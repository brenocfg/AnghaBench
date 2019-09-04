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
 scalar_t__ fs_event_cb_called ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  uv_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fs_event_cb_file_current_dir(uv_fs_event_t* handle,
                                         const char* filename,
                                         int events,
                                         int status) {
  ASSERT(fs_event_cb_called == 0);
  ++fs_event_cb_called;
  ASSERT(status == 0);
#if defined(__APPLE__) || defined(__linux__)
  ASSERT(strcmp(filename, "watch_file") == 0);
#else
  ASSERT(filename == NULL || strcmp(filename, "watch_file") == 0);
#endif
  uv_close((uv_handle_t*)handle, NULL);
}