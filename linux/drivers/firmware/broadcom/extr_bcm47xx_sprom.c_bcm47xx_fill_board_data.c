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
struct ssb_sprom {int /*<<< orphan*/  boardflags2_hi; int /*<<< orphan*/  boardflags2_lo; int /*<<< orphan*/  boardflags_hi; int /*<<< orphan*/  boardflags_lo; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvram_read_u32_2 (char const*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void bcm47xx_fill_board_data(struct ssb_sprom *sprom, const char *prefix,
				    bool fallback)
{
	nvram_read_u32_2(prefix, "boardflags", &sprom->boardflags_lo,
			 &sprom->boardflags_hi, fallback);
	nvram_read_u32_2(prefix, "boardflags2", &sprom->boardflags2_lo,
			 &sprom->boardflags2_hi, fallback);
}