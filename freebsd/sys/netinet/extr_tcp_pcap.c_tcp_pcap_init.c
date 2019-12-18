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
 int /*<<< orphan*/  EVENTHANDLER_PRI_ANY ; 
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (),int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nmbclusters_change ; 
 int /*<<< orphan*/  tcp_pcap_max_set () ; 

void
tcp_pcap_init(void)
{

	tcp_pcap_max_set();
	EVENTHANDLER_REGISTER(nmbclusters_change, tcp_pcap_max_set,
		NULL, EVENTHANDLER_PRI_ANY);
}