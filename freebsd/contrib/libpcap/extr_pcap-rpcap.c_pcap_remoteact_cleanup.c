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
 int /*<<< orphan*/  closesocket (scalar_t__) ; 
 int /*<<< orphan*/  sock_cleanup () ; 
 scalar_t__ sockmain ; 

void pcap_remoteact_cleanup(void)
{
	/* Very dirty, but it works */
	if (sockmain)
	{
		closesocket(sockmain);

		/* To avoid inconsistencies in the number of sock_init() */
		sock_cleanup();
	}

}