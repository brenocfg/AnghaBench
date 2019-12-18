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
struct seq_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAT_SHOW_603 (struct seq_file*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MMU_FTR_USE_HIGH_BATS ; 
 int /*<<< orphan*/  SPRN_DBAT0L ; 
 int /*<<< orphan*/  SPRN_DBAT0U ; 
 int /*<<< orphan*/  SPRN_DBAT1L ; 
 int /*<<< orphan*/  SPRN_DBAT1U ; 
 int /*<<< orphan*/  SPRN_DBAT2L ; 
 int /*<<< orphan*/  SPRN_DBAT2U ; 
 int /*<<< orphan*/  SPRN_DBAT3L ; 
 int /*<<< orphan*/  SPRN_DBAT3U ; 
 int /*<<< orphan*/  SPRN_DBAT4L ; 
 int /*<<< orphan*/  SPRN_DBAT4U ; 
 int /*<<< orphan*/  SPRN_DBAT5L ; 
 int /*<<< orphan*/  SPRN_DBAT5U ; 
 int /*<<< orphan*/  SPRN_DBAT6L ; 
 int /*<<< orphan*/  SPRN_DBAT6U ; 
 int /*<<< orphan*/  SPRN_DBAT7L ; 
 int /*<<< orphan*/  SPRN_DBAT7U ; 
 int /*<<< orphan*/  SPRN_IBAT0L ; 
 int /*<<< orphan*/  SPRN_IBAT0U ; 
 int /*<<< orphan*/  SPRN_IBAT1L ; 
 int /*<<< orphan*/  SPRN_IBAT1U ; 
 int /*<<< orphan*/  SPRN_IBAT2L ; 
 int /*<<< orphan*/  SPRN_IBAT2U ; 
 int /*<<< orphan*/  SPRN_IBAT3L ; 
 int /*<<< orphan*/  SPRN_IBAT3U ; 
 int /*<<< orphan*/  SPRN_IBAT4L ; 
 int /*<<< orphan*/  SPRN_IBAT4U ; 
 int /*<<< orphan*/  SPRN_IBAT5L ; 
 int /*<<< orphan*/  SPRN_IBAT5U ; 
 int /*<<< orphan*/  SPRN_IBAT6L ; 
 int /*<<< orphan*/  SPRN_IBAT6U ; 
 int /*<<< orphan*/  SPRN_IBAT7L ; 
 int /*<<< orphan*/  SPRN_IBAT7U ; 
 scalar_t__ mmu_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int bats_show_603(struct seq_file *m, void *v)
{
	seq_puts(m, "---[ Instruction Block Address Translation ]---\n");

	BAT_SHOW_603(m, 0, SPRN_IBAT0L, SPRN_IBAT0U, false);
	BAT_SHOW_603(m, 1, SPRN_IBAT1L, SPRN_IBAT1U, false);
	BAT_SHOW_603(m, 2, SPRN_IBAT2L, SPRN_IBAT2U, false);
	BAT_SHOW_603(m, 3, SPRN_IBAT3L, SPRN_IBAT3U, false);
	if (mmu_has_feature(MMU_FTR_USE_HIGH_BATS)) {
		BAT_SHOW_603(m, 4, SPRN_IBAT4L, SPRN_IBAT4U, false);
		BAT_SHOW_603(m, 5, SPRN_IBAT5L, SPRN_IBAT5U, false);
		BAT_SHOW_603(m, 6, SPRN_IBAT6L, SPRN_IBAT6U, false);
		BAT_SHOW_603(m, 7, SPRN_IBAT7L, SPRN_IBAT7U, false);
	}

	seq_puts(m, "\n---[ Data Block Address Translation ]---\n");

	BAT_SHOW_603(m, 0, SPRN_DBAT0L, SPRN_DBAT0U, true);
	BAT_SHOW_603(m, 1, SPRN_DBAT1L, SPRN_DBAT1U, true);
	BAT_SHOW_603(m, 2, SPRN_DBAT2L, SPRN_DBAT2U, true);
	BAT_SHOW_603(m, 3, SPRN_DBAT3L, SPRN_DBAT3U, true);
	if (mmu_has_feature(MMU_FTR_USE_HIGH_BATS)) {
		BAT_SHOW_603(m, 4, SPRN_DBAT4L, SPRN_DBAT4U, true);
		BAT_SHOW_603(m, 5, SPRN_DBAT5L, SPRN_DBAT5U, true);
		BAT_SHOW_603(m, 6, SPRN_DBAT6L, SPRN_DBAT6U, true);
		BAT_SHOW_603(m, 7, SPRN_DBAT7L, SPRN_DBAT7U, true);
	}

	return 0;
}