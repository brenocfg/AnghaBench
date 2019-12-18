#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int linktype; int dlt; } ;

/* Variables and functions */
 int DLT_PFSYNC ; 
 int DLT_PKTAP ; 
 int LINKTYPE_MATCHING_MAX ; 
 int LINKTYPE_MATCHING_MIN ; 
 int LINKTYPE_PFSYNC ; 
 int LINKTYPE_PKTAP ; 
 TYPE_1__* map ; 

int
linktype_to_dlt(int linktype)
{
	int i;

	/*
	 * LINKTYPEs in the matching range that *don't*
	 * have the same value as the corresponding DLTs
	 * because, for some reason, not all OSes have the
	 * same value for that DLT.
	 */
	if (linktype == LINKTYPE_PFSYNC)
		return (DLT_PFSYNC);
	if (linktype == LINKTYPE_PKTAP)
		return (DLT_PKTAP);

	/*
	 * For all other values in the matching range, the LINKTYPE
	 * value is the same as the DLT value.
	 */
	if (linktype >= LINKTYPE_MATCHING_MIN &&
	    linktype <= LINKTYPE_MATCHING_MAX)
		return (linktype);

	/*
	 * Map the values outside that range.
	 */
	for (i = 0; map[i].linktype != -1; i++) {
		if (map[i].linktype == linktype)
			return (map[i].dlt);
	}

	/*
	 * If we don't have an entry for this LINKTYPE, return
	 * the link type value; it may be a DLT from an older
	 * version of libpcap.
	 */
	return linktype;
}