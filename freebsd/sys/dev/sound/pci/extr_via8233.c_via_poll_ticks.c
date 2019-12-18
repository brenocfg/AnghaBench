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
typedef  int uint64_t ;
struct via_info {struct via_chinfo* rch; struct via_chinfo* pch; } ;
struct via_chinfo {scalar_t__ active; int blksz; int /*<<< orphan*/  buffer; int /*<<< orphan*/ * channel; } ;

/* Variables and functions */
 int NDXSCHANS ; 
 int NMSGDCHANS ; 
 int NWRCHANS ; 
 int hz ; 
 scalar_t__ sndbuf_getalign (int /*<<< orphan*/ ) ; 
 int sndbuf_getspd (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
via_poll_ticks(struct via_info *via)
{
	struct via_chinfo *ch;
	int i;
	int ret = hz;
	int pollticks;

	for (i = 0; i < NDXSCHANS + NMSGDCHANS; i++) {
		ch = &via->pch[i];
		if (ch->channel == NULL || ch->active == 0)
			continue;
		pollticks = ((uint64_t)hz * ch->blksz) /
		    ((uint64_t)sndbuf_getalign(ch->buffer) *
		    sndbuf_getspd(ch->buffer));
		pollticks >>= 2;
		if (pollticks > hz)
			pollticks = hz;
		if (pollticks < 1)
			pollticks = 1;
		if (pollticks < ret)
			ret = pollticks;
	}

	for (i = 0; i < NWRCHANS; i++) {
		ch = &via->rch[i];
		if (ch->channel == NULL || ch->active == 0)
			continue;
		pollticks = ((uint64_t)hz * ch->blksz) /
		    ((uint64_t)sndbuf_getalign(ch->buffer) *
		    sndbuf_getspd(ch->buffer));
		pollticks >>= 2;
		if (pollticks > hz)
			pollticks = hz;
		if (pollticks < 1)
			pollticks = 1;
		if (pollticks < ret)
			ret = pollticks;
	}

	return (ret);
}