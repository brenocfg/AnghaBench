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
typedef  int /*<<< orphan*/  interface_receiver_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCKIO () ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  NTP_PORT ; 
 int /*<<< orphan*/  UNBLOCKIO () ; 
 scalar_t__ disable_dynamic_updates ; 
 int /*<<< orphan*/  interrupt_worker_sleep () ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*) ; 
 int update_interfaces (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

void
interface_update(
	interface_receiver_t	receiver,
	void *			data)
{
	int new_interface_found;

	if (disable_dynamic_updates)
		return;

	BLOCKIO();
	new_interface_found = update_interfaces(NTP_PORT, receiver, data);
	UNBLOCKIO();

	if (!new_interface_found)
		return;

#ifdef DEBUG
	msyslog(LOG_DEBUG, "new interface(s) found: waking up resolver");
#endif
	interrupt_worker_sleep();
}