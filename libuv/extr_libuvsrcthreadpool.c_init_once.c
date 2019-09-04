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
 int /*<<< orphan*/  init_threads () ; 
 scalar_t__ pthread_atfork (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_once ; 

__attribute__((used)) static void init_once(void) {
#ifndef _WIN32
  /* Re-initialize the threadpool after fork.
   * Note that this discards the global mutex and condition as well
   * as the work queue.
   */
  if (pthread_atfork(NULL, NULL, &reset_once))
    abort();
#endif
  init_threads();
}