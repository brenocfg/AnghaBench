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
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int FS_TEST_FILE ; 
 int /*<<< orphan*/  MAKE_VALGRIND_HAPPY () ; 
 int /*<<< orphan*/  assert_wait_child (int) ; 
 int /*<<< orphan*/  assert_watch_file_current_dir (int /*<<< orphan*/ *,int) ; 
 int fork () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/ * uv_default_loop () ; 
 scalar_t__ uv_loop_close (int /*<<< orphan*/ *) ; 
 scalar_t__ uv_loop_fork (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_loop_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_update_time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int _do_fork_fs_events_child(int file_or_dir) {
  /* basic fsevents work in the child after a fork */
  pid_t child_pid;
  uv_loop_t loop;

  /* Watch in the parent, prime the loop and/or threads. */
  assert_watch_file_current_dir(uv_default_loop(), file_or_dir);
  child_pid = fork();
  ASSERT(child_pid != -1);

  if (child_pid != 0) {
    /* parent */
    assert_wait_child(child_pid);
  } else {
    /* child */
    /* Ee can watch in a new loop, but dirs only work
       if we're on linux. */
#if defined(__APPLE__)
    file_or_dir = FS_TEST_FILE;
#endif
    printf("Running child\n");
    uv_loop_init(&loop);
    printf("Child first watch\n");
    assert_watch_file_current_dir(&loop, file_or_dir);
    ASSERT(0 == uv_loop_close(&loop));
    printf("Child second watch default loop\n");
    /* Ee can watch in the default loop. */
    ASSERT(0 == uv_loop_fork(uv_default_loop()));
    /* On some platforms (OS X), if we don't update the time now,
     * the timer cb fires before the event loop enters uv__io_poll,
     * instead of after, meaning we don't see the change! This may be
     * a general race.
     */
    uv_update_time(uv_default_loop());
    assert_watch_file_current_dir(uv_default_loop(), file_or_dir);

    /* We can close the parent loop successfully too. This is
       especially important on Apple platforms where if we're not
       careful trying to touch the CFRunLoop, even just to shut it
       down, that we allocated in the FS_TEST_DIR case would crash. */
    ASSERT(0 == uv_loop_close(uv_default_loop()));

    printf("Exiting child \n");
  }

  MAKE_VALGRIND_HAPPY();
  return 0;

}