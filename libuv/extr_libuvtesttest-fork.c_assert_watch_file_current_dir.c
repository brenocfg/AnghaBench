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
typedef  int /*<<< orphan*/  uv_timer_t ;
typedef  int /*<<< orphan*/  uv_loop_t ;
typedef  int /*<<< orphan*/  uv_fs_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  UV_RUN_DEFAULT ; 
 int /*<<< orphan*/  create_file (char*) ; 
 int fs_event_cb_called ; 
 int /*<<< orphan*/  fs_event_cb_file_current_dir ; 
 int /*<<< orphan*/  remove (char*) ; 
 int /*<<< orphan*/  timer_cb_touch ; 
 int timer_cb_touch_called ; 
 int uv_fs_event_init (int /*<<< orphan*/ * const,int /*<<< orphan*/ *) ; 
 int uv_fs_event_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_run (int /*<<< orphan*/ * const,int /*<<< orphan*/ ) ; 
 int uv_timer_init (int /*<<< orphan*/ * const,int /*<<< orphan*/ *) ; 
 int uv_timer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void assert_watch_file_current_dir(uv_loop_t* const loop, int file_or_dir) {
  uv_timer_t timer;
  uv_fs_event_t fs_event;
  int r;

  /* Setup */
  remove("watch_file");
  create_file("watch_file");

  r = uv_fs_event_init(loop, &fs_event);
  ASSERT(r == 0);
  /* watching a dir is the only way to get fsevents involved on apple
     platforms */
  r = uv_fs_event_start(&fs_event,
                        fs_event_cb_file_current_dir,
                        file_or_dir == 1 ? "." : "watch_file",
                        0);
  ASSERT(r == 0);

  r = uv_timer_init(loop, &timer);
  ASSERT(r == 0);

  r = uv_timer_start(&timer, timer_cb_touch, 100, 0);
  ASSERT(r == 0);

  ASSERT(timer_cb_touch_called == 0);
  ASSERT(fs_event_cb_called == 0);

  uv_run(loop, UV_RUN_DEFAULT);

  ASSERT(timer_cb_touch_called == 1);
  ASSERT(fs_event_cb_called == 1);

  /* Cleanup */
  remove("watch_file");
  fs_event_cb_called = 0;
  timer_cb_touch_called = 0;
  uv_run(loop, UV_RUN_DEFAULT); /* flush pending closes */
}