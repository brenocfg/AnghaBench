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
typedef  int /*<<< orphan*/  uv_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  close_cb ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,long) ; 
 int /*<<< orphan*/  repeat_1 ; 
 int repeat_1_cb_called ; 
 int /*<<< orphan*/  repeat_2 ; 
 int repeat_2_cb_allowed ; 
 scalar_t__ start_time ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  uv_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_default_loop () ; 
 scalar_t__ uv_now (int /*<<< orphan*/ ) ; 
 int uv_timer_again (int /*<<< orphan*/ *) ; 
 int uv_timer_get_repeat (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void repeat_1_cb(uv_timer_t* handle) {
  int r;

  ASSERT(handle == &repeat_1);
  ASSERT(uv_timer_get_repeat((uv_timer_t*)handle) == 50);

  fprintf(stderr, "repeat_1_cb called after %ld ms\n",
          (long int)(uv_now(uv_default_loop()) - start_time));
  fflush(stderr);

  repeat_1_cb_called++;

  r = uv_timer_again(&repeat_2);
  ASSERT(r == 0);

  if (repeat_1_cb_called == 10) {
    uv_close((uv_handle_t*)handle, close_cb);
    /* We're not calling uv_timer_again on repeat_2 any more, so after this
     * timer_2_cb is expected. */
    repeat_2_cb_allowed = 1;
    return;
  }
}