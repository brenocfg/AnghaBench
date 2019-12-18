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
typedef  int /*<<< orphan*/  uv_prepare_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int ITERATIONS ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int loop_iteration ; 
 int /*<<< orphan*/  prepare_1_cb_called ; 
 int /*<<< orphan*/  prepare_1_handle ; 
 int /*<<< orphan*/  prepare_2_cb ; 
 int /*<<< orphan*/  prepare_2_handle ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int /*<<< orphan*/  stderr ; 
 int uv_prepare_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void prepare_1_cb(uv_prepare_t* handle) {
  int r;

  fprintf(stderr, "%s", "PREPARE_1_CB\n");
  fflush(stderr);
  ASSERT(handle == &prepare_1_handle);

  if (loop_iteration % 2 == 0) {
    r = uv_prepare_start(&prepare_2_handle, prepare_2_cb);
    ASSERT(r == 0);
  }

  prepare_1_cb_called++;
  loop_iteration++;

  printf("Loop iteration %d of %d.\n", loop_iteration, ITERATIONS);
}