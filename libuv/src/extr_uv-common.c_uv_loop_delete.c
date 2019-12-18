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

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * default_loop_ptr ; 
 int /*<<< orphan*/  uv__free (int /*<<< orphan*/ *) ; 
 int uv_loop_close (int /*<<< orphan*/ *) ; 

void uv_loop_delete(uv_loop_t* loop) {
  uv_loop_t* default_loop;
  int err;

  default_loop = default_loop_ptr;

  err = uv_loop_close(loop);
  (void) err;    /* Squelch compiler warnings. */
  assert(err == 0);
  if (loop != default_loop)
    uv__free(loop);
}