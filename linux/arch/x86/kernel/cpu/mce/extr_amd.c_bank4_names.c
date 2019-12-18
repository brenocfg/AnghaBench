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
struct threshold_block {int address; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*,int) ; 

__attribute__((used)) static const char *bank4_names(const struct threshold_block *b)
{
	switch (b->address) {
	/* MSR4_MISC0 */
	case 0x00000413:
		return "dram";

	case 0xc0000408:
		return "ht_links";

	case 0xc0000409:
		return "l3_cache";

	default:
		WARN(1, "Funny MSR: 0x%08x\n", b->address);
		return "";
	}
}