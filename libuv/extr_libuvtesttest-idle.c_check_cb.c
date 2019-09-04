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
typedef  int /*<<< orphan*/  uv_check_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int check_cb_called ; 
 int /*<<< orphan*/  check_handle ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void check_cb(uv_check_t* handle) {
  ASSERT(handle == &check_handle);

  check_cb_called++;
  fprintf(stderr, "check_cb %d\n", check_cb_called);
  fflush(stderr);
}