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
struct tcp_hpts_entry {int /*<<< orphan*/  ie_cookie; } ;

/* Variables and functions */
 int /*<<< orphan*/  swi_sched (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hpts_timeout_swi(void *arg)
{
	struct tcp_hpts_entry *hpts;

	hpts = (struct tcp_hpts_entry *)arg;
	swi_sched(hpts->ie_cookie, 0);
}