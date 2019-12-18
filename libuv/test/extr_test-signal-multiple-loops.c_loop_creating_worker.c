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
typedef  int /*<<< orphan*/  uv_signal_t ;
typedef  int /*<<< orphan*/  uv_loop_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  UV_RUN_DEFAULT ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  increment_counter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  loop_creation_counter ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  signal_unexpected_cb ; 
 int /*<<< orphan*/  stop ; 
 int /*<<< orphan*/  uv_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_loop_close (int /*<<< orphan*/ *) ; 
 scalar_t__ uv_loop_init (int /*<<< orphan*/ *) ; 
 int uv_run (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int uv_signal_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int uv_signal_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void loop_creating_worker(void* context) {
  (void) context;

  do {
    uv_loop_t *loop;
    uv_signal_t signal;
    int r;

    loop = malloc(sizeof(*loop));
    ASSERT(loop != NULL);
    ASSERT(0 == uv_loop_init(loop));

    r = uv_signal_init(loop, &signal);
    ASSERT(r == 0);

    r = uv_signal_start(&signal, signal_unexpected_cb, SIGTERM);
    ASSERT(r == 0);

    uv_close((uv_handle_t*) &signal, NULL);

    r = uv_run(loop, UV_RUN_DEFAULT);
    ASSERT(r == 0);

    uv_loop_close(loop);
    free(loop);

    increment_counter(&loop_creation_counter);
  } while (!stop);
}