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
struct ub_event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AS_EVENT (struct ub_event*) ; 
 int /*<<< orphan*/  NATIVE_BITS (int) ; 
 int /*<<< orphan*/  winsock_tcp_wouldblock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ub_winsock_tcp_wouldblock(struct ub_event* ev, int eventbits)
{
#if defined(USE_MINI_EVENT) && defined(USE_WINSOCK)
	winsock_tcp_wouldblock(AS_EVENT(ev), NATIVE_BITS(eventbits));
#else
	(void)ev;
	(void)eventbits;
#endif
}