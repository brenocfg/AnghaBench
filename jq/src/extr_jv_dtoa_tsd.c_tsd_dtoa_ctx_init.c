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

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtoa_ctx_key ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pthread_key_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  tsd_dtoa_ctx_dtor ; 
 int /*<<< orphan*/  tsd_dtoa_ctx_fini ; 

__attribute__((used)) static void tsd_dtoa_ctx_init() {
  if (pthread_key_create(&dtoa_ctx_key, tsd_dtoa_ctx_dtor) != 0) {
    fprintf(stderr, "error: cannot create thread specific key");
    abort();
  }
  atexit(tsd_dtoa_ctx_fini);
}