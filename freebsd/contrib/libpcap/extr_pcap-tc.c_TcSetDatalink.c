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
typedef  int /*<<< orphan*/  pcap_t ;

/* Variables and functions */

__attribute__((used)) static int TcSetDatalink(pcap_t *p, int dlt)
{
	/*
	 * We don't have to do any work here; pcap_set_datalink() checks
	 * whether the value is in the list of DLT_ values we
	 * supplied, so we don't have to, and, if it is valid, sets
	 * p->linktype to the new value; we don't have to do anything
	 * in hardware, we just use what's in p->linktype.
	 *
	 * We do have to have a routine, however, so that pcap_set_datalink()
	 * doesn't think we don't support setting the link-layer header
	 * type at all.
	 */
	return 0;
}