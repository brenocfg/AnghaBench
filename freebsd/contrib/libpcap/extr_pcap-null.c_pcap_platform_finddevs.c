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
typedef  int /*<<< orphan*/  pcap_if_list_t ;

/* Variables and functions */

int
pcap_platform_finddevs(pcap_if_list_t *devlistp, char *errbuf)
{
	/*
	 * There are no interfaces on which we can capture.
	 */
	return (0);
}