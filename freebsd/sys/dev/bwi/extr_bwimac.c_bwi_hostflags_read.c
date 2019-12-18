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
typedef  int uint64_t ;
struct bwi_mac {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWI_COMM_MOBJ ; 
 int /*<<< orphan*/  BWI_COMM_MOBJ_HFLAGS_LO ; 
 int /*<<< orphan*/  BWI_COMM_MOBJ_HFLAGS_MI ; 
 int MOBJ_READ_2 (struct bwi_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

uint64_t
bwi_hostflags_read(struct bwi_mac *mac)
{
	uint64_t flags, val;

	/* HI has unclear meaning, so don't touch it */
	flags = 0;

	val = MOBJ_READ_2(mac, BWI_COMM_MOBJ, BWI_COMM_MOBJ_HFLAGS_MI);
	flags |= val << 16;

	val = MOBJ_READ_2(mac, BWI_COMM_MOBJ, BWI_COMM_MOBJ_HFLAGS_LO);
	flags |= val;

	return flags;
}