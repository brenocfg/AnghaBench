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
 scalar_t__ uv__make_pipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__signal_global_fini () ; 
 int /*<<< orphan*/  uv__signal_lock_pipefd ; 
 scalar_t__ uv__signal_unlock () ; 

__attribute__((used)) static void uv__signal_global_reinit(void) {
  uv__signal_global_fini();

  if (uv__make_pipe(uv__signal_lock_pipefd, 0))
    abort();

  if (uv__signal_unlock())
    abort();
}