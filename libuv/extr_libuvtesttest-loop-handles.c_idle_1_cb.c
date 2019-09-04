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
typedef  int /*<<< orphan*/  uv_idle_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int idle_1_cb_called ; 
 int /*<<< orphan*/  idle_2_cb ; 
 int /*<<< orphan*/  idle_2_cb_started ; 
 int /*<<< orphan*/  idle_2_handle ; 
 int idle_2_is_active ; 
 scalar_t__ idles_1_active ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  uv_default_loop () ; 
 int uv_idle_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int uv_idle_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int uv_idle_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_is_closing (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void idle_1_cb(uv_idle_t* handle) {
  int r;

  fprintf(stderr, "%s", "IDLE_1_CB\n");
  fflush(stderr);

  ASSERT(handle != NULL);
  ASSERT(idles_1_active > 0);

  /* Init idle_2 and make it active */
  if (!idle_2_is_active && !uv_is_closing((uv_handle_t*)&idle_2_handle)) {
    r = uv_idle_init(uv_default_loop(), &idle_2_handle);
    ASSERT(r == 0);
    r = uv_idle_start(&idle_2_handle, idle_2_cb);
    ASSERT(r == 0);
    idle_2_is_active = 1;
    idle_2_cb_started++;
  }

  idle_1_cb_called++;

  if (idle_1_cb_called % 5 == 0) {
    r = uv_idle_stop((uv_idle_t*)handle);
    ASSERT(r == 0);
    idles_1_active--;
  }
}