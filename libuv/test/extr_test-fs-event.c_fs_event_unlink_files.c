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

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int fs_event_file_count ; 
 int /*<<< orphan*/  fs_event_get_filename (int) ; 
 int fs_event_removed ; 
 int remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer ; 
 scalar_t__ uv_timer_start (int /*<<< orphan*/ *,void (*) (int /*<<< orphan*/ *),int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fs_event_unlink_files(uv_timer_t* handle) {
  int r;
  int i;

  /* NOTE: handle might be NULL if invoked not as timer callback */
  if (handle == NULL) {
    /* Unlink all files */
    for (i = 0; i < 16; i++) {
      r = remove(fs_event_get_filename(i));
      if (handle != NULL)
        ASSERT(r == 0);
    }
  } else {
    /* Make sure we're not attempting to remove files we do not intend */
    ASSERT(fs_event_removed < fs_event_file_count);

    /* Remove the file */
    ASSERT(0 == remove(fs_event_get_filename(fs_event_removed)));

    if (++fs_event_removed < fs_event_file_count) {
      /* Remove another file on a different event loop tick.  We do it this way
       * to avoid fs events coalescing into one fs event. */
      ASSERT(0 == uv_timer_start(&timer, fs_event_unlink_files, 1, 0));
    }
  }
}