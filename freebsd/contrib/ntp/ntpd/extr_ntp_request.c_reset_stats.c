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
typedef  int u_long ;
struct reset_flags {int /*<<< orphan*/  flags; } ;
struct reset_entry {int flag; int /*<<< orphan*/  (* handler ) () ;} ;
struct req_pkt {int /*<<< orphan*/  u; int /*<<< orphan*/  err_nitems; } ;
typedef  int /*<<< orphan*/  sockaddr_u ;
typedef  int /*<<< orphan*/  endpt ;

/* Variables and functions */
 int /*<<< orphan*/  INFO_ERR_FMT ; 
 int INFO_NITEMS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INFO_OKAY ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int RESET_ALLFLAGS ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,...) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  req_ack (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct req_pkt*,int /*<<< orphan*/ ) ; 
 struct reset_entry* reset_entries ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static void
reset_stats(
	sockaddr_u *srcadr,
	endpt *inter,
	struct req_pkt *inpkt
	)
{
	struct reset_flags *rflags;
	u_long flags;
	struct reset_entry *rent;

	if (INFO_NITEMS(inpkt->err_nitems) > 1) {
		msyslog(LOG_ERR, "reset_stats: err_nitems > 1");
		req_ack(srcadr, inter, inpkt, INFO_ERR_FMT);
		return;
	}

	rflags = (struct reset_flags *)&inpkt->u;
	flags = ntohl(rflags->flags);

	if (flags & ~RESET_ALLFLAGS) {
		msyslog(LOG_ERR, "reset_stats: reset leaves %#lx",
			flags & ~RESET_ALLFLAGS);
		req_ack(srcadr, inter, inpkt, INFO_ERR_FMT);
		return;
	}

	for (rent = reset_entries; rent->flag != 0; rent++) {
		if (flags & rent->flag)
			(*rent->handler)();
	}
	req_ack(srcadr, inter, inpkt, INFO_OKAY);
}