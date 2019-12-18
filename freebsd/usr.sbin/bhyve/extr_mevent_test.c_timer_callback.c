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
typedef  enum ev_type { ____Placeholder_ev_type } ev_type ;

/* Variables and functions */
 int TEVSZ ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  mevent_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdtsc () ; 
 int /*<<< orphan*/ * tevbuf ; 
 int /*<<< orphan*/  tevp ; 
 int /*<<< orphan*/  timer_print () ; 

__attribute__((used)) static void
timer_callback(int fd, enum ev_type type, void *param)
{
	static int i;

	if (i >= TEVSZ)
		abort();

	tevbuf[i++] = rdtsc();

	if (i == TEVSZ) {
		mevent_delete(tevp);
		timer_print();
	}
}