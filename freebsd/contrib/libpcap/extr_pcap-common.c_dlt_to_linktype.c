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
struct TYPE_2__ {int dlt; int linktype; } ;

/* Variables and functions */
 int DLT_MATCHING_MAX ; 
 int DLT_MATCHING_MIN ; 
 int DLT_PFSYNC ; 
 int DLT_PKTAP ; 
 int LINKTYPE_PFSYNC ; 
 int LINKTYPE_PKTAP ; 
 TYPE_1__* map ; 

int
dlt_to_linktype(int dlt)
{
	int i;

	/*
	 * DLTs that, on some platforms, have values in the matching range
	 * but that *don't* have the same value as the corresponding
	 * LINKTYPE because, for some reason, not all OSes have the
	 * same value for that DLT (note that the DLT's value might be
	 * outside the matching range on some of those OSes).
	 */
	if (dlt == DLT_PFSYNC)
		return (LINKTYPE_PFSYNC);
	if (dlt == DLT_PKTAP)
		return (LINKTYPE_PKTAP);

	/*
	 * For all other values in the matching range, the DLT
	 * value is the same as the LINKTYPE value.
	 */
	if (dlt >= DLT_MATCHING_MIN && dlt <= DLT_MATCHING_MAX)
		return (dlt);

	/*
	 * Map the values outside that range.
	 */
	for (i = 0; map[i].dlt != -1; i++) {
		if (map[i].dlt == dlt)
			return (map[i].linktype);
	}

	/*
	 * If we don't have a mapping for this DLT, return an
	 * error; that means that this is a value with no corresponding
	 * LINKTYPE, and we need to assign one.
	 */
	return (-1);
}