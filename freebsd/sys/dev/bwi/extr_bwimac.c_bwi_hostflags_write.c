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
 int /*<<< orphan*/  MOBJ_WRITE_2 (struct bwi_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
bwi_hostflags_write(struct bwi_mac *mac, uint64_t flags)
{
	uint64_t val;

	val = flags & 0xffff;
	MOBJ_WRITE_2(mac, BWI_COMM_MOBJ, BWI_COMM_MOBJ_HFLAGS_LO, val);

	val = (flags >> 16) & 0xffff;
	MOBJ_WRITE_2(mac, BWI_COMM_MOBJ, BWI_COMM_MOBJ_HFLAGS_MI, val);

	/* HI has unclear meaning, so leave it as it is */
}