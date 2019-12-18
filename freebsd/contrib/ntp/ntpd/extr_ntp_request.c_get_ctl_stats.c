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
typedef  int /*<<< orphan*/  u_int32 ;
struct req_pkt {int dummy; } ;
struct info_control {void* numasyncmsgs; void* numctlbadop; void* numctldatatooshort; void* numctlbadversion; void* numctlbadoffset; void* numctlinputerr; void* numctlinputfrag; void* numctlinputresp; void* numctltooshort; void* numctlerrors; void* numctlfrags; void* numctlresponses; void* numctlbadpkts; void* numctlreq; void* ctltimereset; } ;
typedef  int /*<<< orphan*/  sockaddr_u ;
typedef  int /*<<< orphan*/  endpt ;

/* Variables and functions */
 scalar_t__ ctltimereset ; 
 scalar_t__ current_time ; 
 int /*<<< orphan*/  flush_pkt () ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  more_pkt () ; 
 scalar_t__ numasyncmsgs ; 
 scalar_t__ numctlbadoffset ; 
 scalar_t__ numctlbadop ; 
 scalar_t__ numctlbadpkts ; 
 scalar_t__ numctlbadversion ; 
 scalar_t__ numctldatatooshort ; 
 scalar_t__ numctlerrors ; 
 scalar_t__ numctlfrags ; 
 scalar_t__ numctlinputerr ; 
 scalar_t__ numctlinputfrag ; 
 scalar_t__ numctlinputresp ; 
 scalar_t__ numctlreq ; 
 scalar_t__ numctlresponses ; 
 scalar_t__ numctltooshort ; 
 scalar_t__ prepare_pkt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct req_pkt*,int) ; 

__attribute__((used)) static void
get_ctl_stats(
	sockaddr_u *srcadr,
	endpt *inter,
	struct req_pkt *inpkt
	)
{
	register struct info_control *ic;

	ic = (struct info_control *)prepare_pkt(srcadr, inter, inpkt,
						sizeof(struct info_control));

	ic->ctltimereset = htonl((u_int32)(current_time - ctltimereset));
	ic->numctlreq = htonl((u_int32)numctlreq);
	ic->numctlbadpkts = htonl((u_int32)numctlbadpkts);
	ic->numctlresponses = htonl((u_int32)numctlresponses);
	ic->numctlfrags = htonl((u_int32)numctlfrags);
	ic->numctlerrors = htonl((u_int32)numctlerrors);
	ic->numctltooshort = htonl((u_int32)numctltooshort);
	ic->numctlinputresp = htonl((u_int32)numctlinputresp);
	ic->numctlinputfrag = htonl((u_int32)numctlinputfrag);
	ic->numctlinputerr = htonl((u_int32)numctlinputerr);
	ic->numctlbadoffset = htonl((u_int32)numctlbadoffset);
	ic->numctlbadversion = htonl((u_int32)numctlbadversion);
	ic->numctldatatooshort = htonl((u_int32)numctldatatooshort);
	ic->numctlbadop = htonl((u_int32)numctlbadop);
	ic->numasyncmsgs = htonl((u_int32)numasyncmsgs);

	(void) more_pkt();
	flush_pkt();
}