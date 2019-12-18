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
 int /*<<< orphan*/  SIGALRM ; 
 scalar_t__ count ; 
 int /*<<< orphan*/  done ; 
 int /*<<< orphan*/  env ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,void (*) ()) ; 
 int /*<<< orphan*/  tick () ; 

__attribute__((used)) static void
interrupt()
{
	if (count) {
#ifdef OLD_TRUERAND
		longjmp(env, 1);
#else
		++done;
		return;
#endif
	}

	(void) signal(SIGALRM, interrupt);
	tick();
}