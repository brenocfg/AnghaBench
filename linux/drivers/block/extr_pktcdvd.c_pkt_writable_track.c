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
struct TYPE_3__ {int rt; int blank; int /*<<< orphan*/  packet; int /*<<< orphan*/  fp; } ;
typedef  TYPE_1__ track_information ;
struct pktcdvd_device {int mmc3_profile; } ;

/* Variables and functions */
 int /*<<< orphan*/  pkt_err (struct pktcdvd_device*,char*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pkt_writable_track(struct pktcdvd_device *pd, track_information *ti)
{
	switch (pd->mmc3_profile) {
		case 0x1a: /* DVD+RW */
		case 0x12: /* DVD-RAM */
			/* The track is always writable on DVD+RW/DVD-RAM */
			return 1;
		default:
			break;
	}

	if (!ti->packet || !ti->fp)
		return 0;

	/*
	 * "good" settings as per Mt Fuji.
	 */
	if (ti->rt == 0 && ti->blank == 0)
		return 1;

	if (ti->rt == 0 && ti->blank == 1)
		return 1;

	if (ti->rt == 1 && ti->blank == 0)
		return 1;

	pkt_err(pd, "bad state %d-%d-%d\n", ti->rt, ti->blank, ti->packet);
	return 0;
}