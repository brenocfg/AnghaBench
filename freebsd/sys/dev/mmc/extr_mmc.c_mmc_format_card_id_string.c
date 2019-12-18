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
typedef  int uint8_t ;
struct TYPE_2__ {int oid; int psn; int pnm; int prv; int mdt_month; int mdt_year; char* mid; } ;
struct mmc_ivars {scalar_t__ mode; TYPE_1__ cid; scalar_t__ high_cap; int /*<<< orphan*/  card_id_string; int /*<<< orphan*/  card_sn_string; } ;
typedef  int /*<<< orphan*/  oidstr ;

/* Variables and functions */
 scalar_t__ mode_sd ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 

__attribute__((used)) static void
mmc_format_card_id_string(struct mmc_ivars *ivar)
{
	char oidstr[8];
	uint8_t c1;
	uint8_t c2;

	/*
	 * Format a card ID string for use by the mmcsd driver, it's what
	 * appears between the <> in the following:
	 * mmcsd0: 968MB <SD SD01G 8.0 SN 2686905 MFG 08/2008 by 3 TN> at mmc0
	 * 22.5MHz/4bit/128-block
	 *
	 * Also format just the card serial number, which the mmcsd driver will
	 * use as the disk->d_ident string.
	 *
	 * The card_id_string in mmc_ivars is currently allocated as 64 bytes,
	 * and our max formatted length is currently 55 bytes if every field
	 * contains the largest value.
	 *
	 * Sometimes the oid is two printable ascii chars; when it's not,
	 * format it as 0xnnnn instead.
	 */
	c1 = (ivar->cid.oid >> 8) & 0x0ff;
	c2 = ivar->cid.oid & 0x0ff;
	if (c1 > 0x1f && c1 < 0x7f && c2 > 0x1f && c2 < 0x7f)
		snprintf(oidstr, sizeof(oidstr), "%c%c", c1, c2);
	else
		snprintf(oidstr, sizeof(oidstr), "0x%04x", ivar->cid.oid);
	snprintf(ivar->card_sn_string, sizeof(ivar->card_sn_string),
	    "%08X", ivar->cid.psn);
	snprintf(ivar->card_id_string, sizeof(ivar->card_id_string),
	    "%s%s %s %d.%d SN %08X MFG %02d/%04d by %d %s",
	    ivar->mode == mode_sd ? "SD" : "MMC", ivar->high_cap ? "HC" : "",
	    ivar->cid.pnm, ivar->cid.prv >> 4, ivar->cid.prv & 0x0f,
	    ivar->cid.psn, ivar->cid.mdt_month, ivar->cid.mdt_year,
	    ivar->cid.mid, oidstr);
}