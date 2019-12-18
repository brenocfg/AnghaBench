#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pktcdvd_device {int mmc3_profile; } ;
struct TYPE_3__ {int disc_type; scalar_t__ erasable; scalar_t__ border_status; } ;
typedef  TYPE_1__ disc_information ;

/* Variables and functions */
 scalar_t__ PACKET_SESSION_RESERVED ; 
 int /*<<< orphan*/  pkt_dbg (int,struct pktcdvd_device*,char*,int) ; 
 int /*<<< orphan*/  pkt_err (struct pktcdvd_device*,char*,...) ; 
 int /*<<< orphan*/  pkt_notice (struct pktcdvd_device*,char*) ; 

__attribute__((used)) static int pkt_writable_disc(struct pktcdvd_device *pd, disc_information *di)
{
	switch (pd->mmc3_profile) {
		case 0x0a: /* CD-RW */
		case 0xffff: /* MMC3 not supported */
			break;
		case 0x1a: /* DVD+RW */
		case 0x13: /* DVD-RW */
		case 0x12: /* DVD-RAM */
			return 1;
		default:
			pkt_dbg(2, pd, "Wrong disc profile (%x)\n",
				pd->mmc3_profile);
			return 0;
	}

	/*
	 * for disc type 0xff we should probably reserve a new track.
	 * but i'm not sure, should we leave this to user apps? probably.
	 */
	if (di->disc_type == 0xff) {
		pkt_notice(pd, "unknown disc - no track?\n");
		return 0;
	}

	if (di->disc_type != 0x20 && di->disc_type != 0) {
		pkt_err(pd, "wrong disc type (%x)\n", di->disc_type);
		return 0;
	}

	if (di->erasable == 0) {
		pkt_notice(pd, "disc not erasable\n");
		return 0;
	}

	if (di->border_status == PACKET_SESSION_RESERVED) {
		pkt_err(pd, "can't write to last track (reserved)\n");
		return 0;
	}

	return 1;
}