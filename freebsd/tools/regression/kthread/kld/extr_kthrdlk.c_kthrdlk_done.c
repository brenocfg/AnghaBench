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
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int EWOULDBLOCK ; 
 int QUIT ; 
 int /*<<< orphan*/  global_condvar ; 
 int hz ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int mtx_sleep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  panic (char*,scalar_t__) ; 
 int /*<<< orphan*/  test_global_lock ; 
 scalar_t__ test_thrcnt ; 

__attribute__((used)) static void
kthrdlk_done(void)
{
	int ret;
	DPRINTF(("sending QUIT signal to the thrdlk threads\n"));

	/* wait kernel threads end */
	mtx_lock(&test_global_lock);
	QUIT = 1;
	while (test_thrcnt != 0) {
		ret = mtx_sleep(&global_condvar, &test_global_lock, 0, "waiting thrs end", 30 * hz);
		if (ret == EWOULDBLOCK) {
			panic("some threads not die! remaining: %d", test_thrcnt);
			break;
		}
	}
	if (test_thrcnt == 0)
		DPRINTF(("All test_pause threads die\n"));

	mtx_destroy(&test_global_lock);
}