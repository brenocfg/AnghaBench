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
 int /*<<< orphan*/  CREATE_TIMEOUT ; 
 int /*<<< orphan*/  create_file (int /*<<< orphan*/ ) ; 
 scalar_t__ fs_event_created ; 
 scalar_t__ fs_event_file_count ; 
 int /*<<< orphan*/  fs_event_get_filename (scalar_t__) ; 
 int /*<<< orphan*/  timer ; 
 scalar_t__ uv_timer_start (int /*<<< orphan*/ *,void (*) (int /*<<< orphan*/ *),int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fs_event_create_files(uv_timer_t* handle) {
  /* Make sure we're not attempting to create files we do not intend */
  ASSERT(fs_event_created < fs_event_file_count);

  /* Create the file */
  create_file(fs_event_get_filename(fs_event_created));

  if (++fs_event_created < fs_event_file_count) {
    /* Create another file on a different event loop tick.  We do it this way
     * to avoid fs events coalescing into one fs event. */
    ASSERT(0 == uv_timer_start(&timer,
                               fs_event_create_files,
                               CREATE_TIMEOUT,
                               0));
  }
}