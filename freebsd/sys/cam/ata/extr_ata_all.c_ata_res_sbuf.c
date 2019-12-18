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
struct ata_res {int /*<<< orphan*/  sector_count_exp; int /*<<< orphan*/  sector_count; int /*<<< orphan*/  lba_high_exp; int /*<<< orphan*/  lba_mid_exp; int /*<<< orphan*/  lba_low_exp; int /*<<< orphan*/  device; int /*<<< orphan*/  lba_high; int /*<<< orphan*/  lba_mid; int /*<<< orphan*/  lba_low; int /*<<< orphan*/  error; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ata_res_sbuf(struct ata_res *res, struct sbuf *sb)
{

	sbuf_printf(sb, "%02x %02x %02x %02x "
	    "%02x %02x %02x %02x %02x %02x %02x",
	    res->status, res->error,
	    res->lba_low, res->lba_mid, res->lba_high, res->device,
	    res->lba_low_exp, res->lba_mid_exp, res->lba_high_exp,
	    res->sector_count, res->sector_count_exp);

	return (0);
}