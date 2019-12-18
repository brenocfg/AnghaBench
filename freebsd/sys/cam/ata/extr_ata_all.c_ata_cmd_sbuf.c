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
struct sbuf {int dummy; } ;
struct ata_cmd {int /*<<< orphan*/  sector_count_exp; int /*<<< orphan*/  sector_count; int /*<<< orphan*/  features_exp; int /*<<< orphan*/  lba_high_exp; int /*<<< orphan*/  lba_mid_exp; int /*<<< orphan*/  lba_low_exp; int /*<<< orphan*/  device; int /*<<< orphan*/  lba_high; int /*<<< orphan*/  lba_mid; int /*<<< orphan*/  lba_low; int /*<<< orphan*/  features; int /*<<< orphan*/  command; } ;

/* Variables and functions */
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ata_cmd_sbuf(struct ata_cmd *cmd, struct sbuf *sb)
{
	sbuf_printf(sb, "%02x %02x %02x %02x "
	    "%02x %02x %02x %02x %02x %02x %02x %02x",
	    cmd->command, cmd->features,
	    cmd->lba_low, cmd->lba_mid, cmd->lba_high, cmd->device,
	    cmd->lba_low_exp, cmd->lba_mid_exp, cmd->lba_high_exp,
	    cmd->features_exp, cmd->sector_count, cmd->sector_count_exp);
}