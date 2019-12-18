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
typedef  int /*<<< orphan*/  uint32_t ;
struct via_info {int dummy; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int VIA_AC97_CODEC00_VALID ; 
 int /*<<< orphan*/  VIA_AC97_CONTROL ; 
 int VIA_AC97_DATA (int /*<<< orphan*/ ) ; 
 int VIA_AC97_INDEX (int) ; 
 scalar_t__ via_waitready_codec (struct via_info*) ; 
 int /*<<< orphan*/  via_wr (struct via_info*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
via_write_codec(kobj_t obj, void *addr, int reg, uint32_t val)
{
	struct via_info *via = addr;

	if (via_waitready_codec(via))
		return (-1);

	via_wr(via, VIA_AC97_CONTROL,
	       VIA_AC97_CODEC00_VALID | VIA_AC97_INDEX(reg) |
	       VIA_AC97_DATA(val), 4);

	return (0);
}