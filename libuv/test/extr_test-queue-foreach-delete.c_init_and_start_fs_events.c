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
typedef  int /*<<< orphan*/  uv_fs_event_cb ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/ * fs_event ; 
 scalar_t__* fs_event_cbs ; 
 int uv_fs_event_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int uv_fs_event_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  watched_dir ; 

__attribute__((used)) static void init_and_start_fs_events(uv_loop_t* loop) {
  size_t i;
  for (i = 0; i < ARRAY_SIZE(fs_event); i++) {
    int r;
    r = uv_fs_event_init(loop, &fs_event[i]);
    ASSERT(r == 0);

    r = uv_fs_event_start(&fs_event[i],
                          (uv_fs_event_cb)fs_event_cbs[i],
                          watched_dir,
                          0);
    ASSERT(r == 0);
  }
}