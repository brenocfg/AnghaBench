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
struct mpt_query_disk {char const* devname; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int U8 ;

/* Variables and functions */
 scalar_t__ mpt_query_disk (int,int,struct mpt_query_disk*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,...) ; 

const char *
mpt_volume_name(U8 VolumeBus, U8 VolumeID)
{
	static struct mpt_query_disk info;
	static char buf[16];

	if (mpt_query_disk(VolumeBus, VolumeID, &info) != 0) {
		/*
		 * We only print out the bus number if it is non-zero
		 * since mpt(4) only supports devices on bus zero
		 * anyway.
		 */
		if (VolumeBus == 0)
			snprintf(buf, sizeof(buf), "%d", VolumeID);
		else
			snprintf(buf, sizeof(buf), "%d:%d", VolumeBus,
			    VolumeID);
		return (buf);
	}
	return (info.devname);
}