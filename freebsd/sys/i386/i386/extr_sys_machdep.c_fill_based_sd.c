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
typedef  int uint32_t ;
struct segment_descriptor {int sd_lobase; int sd_hibase; int sd_lolimit; int sd_hilimit; int sd_p; int sd_def32; int sd_gran; scalar_t__ sd_xx; int /*<<< orphan*/  sd_dpl; int /*<<< orphan*/  sd_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDT_MEMRWA ; 
 int /*<<< orphan*/  SEL_UPL ; 

void
fill_based_sd(struct segment_descriptor *sdp, uint32_t base)
{

	sdp->sd_lobase = base & 0xffffff;
	sdp->sd_hibase = (base >> 24) & 0xff;
	sdp->sd_lolimit = 0xffff;	/* 4GB limit, wraps around */
	sdp->sd_hilimit = 0xf;
	sdp->sd_type = SDT_MEMRWA;
	sdp->sd_dpl = SEL_UPL;
	sdp->sd_p = 1;
	sdp->sd_xx = 0;
	sdp->sd_def32 = 1;
	sdp->sd_gran = 1;
}