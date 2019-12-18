#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
struct lqrdata {int PeerInLQRs; int LastOutLQRs; int LastOutPackets; int PeerInPackets; int LastOutOctets; int PeerInOctets; int PeerOutPackets; int PeerOutOctets; int PeerInDiscards; int PeerInErrors; } ;
struct TYPE_6__ {int InPackets; int InOctets; } ;
struct TYPE_5__ {int InPackets; int InOctets; } ;
struct TYPE_7__ {int OutLQRs; TYPE_2__ prevSave; TYPE_1__ Save; } ;
struct TYPE_8__ {TYPE_3__ lqr; } ;
struct hdlc {TYPE_4__ lqm; } ;

/* Variables and functions */
 int /*<<< orphan*/  LogLQM ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,...) ; 

void
lqr_Analyse(const struct hdlc *hdlc, const struct lqrdata *oldlqr,
            const struct lqrdata *newlqr)
{
  u_int32_t LQRs, transitLQRs, pkts, octets, disc, err;

  if (!newlqr->PeerInLQRs)	/* No analysis possible yet! */
    return;

  log_Printf(LogLQM, "Analysis:\n");

  LQRs = (newlqr->LastOutLQRs - oldlqr->LastOutLQRs) -
         (newlqr->PeerInLQRs - oldlqr->PeerInLQRs);
  transitLQRs = hdlc->lqm.lqr.OutLQRs - newlqr->LastOutLQRs;
  pkts = (newlqr->LastOutPackets - oldlqr->LastOutPackets) -
         (newlqr->PeerInPackets - oldlqr->PeerInPackets);
  octets = (newlqr->LastOutOctets - oldlqr->LastOutOctets) -
           (newlqr->PeerInOctets - oldlqr->PeerInOctets);
  log_Printf(LogLQM, "  Outbound lossage: %d LQR%s (%d en route), %d packet%s,"
             " %d octet%s\n", (int)LQRs, LQRs == 1 ? "" : "s", (int)transitLQRs,
	     (int)pkts, pkts == 1 ? "" : "s",
	     (int)octets, octets == 1 ? "" : "s");

  pkts = (newlqr->PeerOutPackets - oldlqr->PeerOutPackets) -
    (hdlc->lqm.lqr.Save.InPackets - hdlc->lqm.lqr.prevSave.InPackets);
  octets = (newlqr->PeerOutOctets - oldlqr->PeerOutOctets) -
    (hdlc->lqm.lqr.Save.InOctets - hdlc->lqm.lqr.prevSave.InOctets);
  log_Printf(LogLQM, "  Inbound lossage: %d packet%s, %d octet%s\n",
	     (int)pkts, pkts == 1 ? "" : "s",
	     (int)octets, octets == 1 ? "" : "s");

  disc = newlqr->PeerInDiscards - oldlqr->PeerInDiscards;
  err = newlqr->PeerInErrors - oldlqr->PeerInErrors;
  if (disc && err)
    log_Printf(LogLQM, "                   Likely due to both peer congestion"
               " and physical errors\n");
  else if (disc)
    log_Printf(LogLQM, "                   Likely due to peer congestion\n");
  else if (err)
    log_Printf(LogLQM, "                   Likely due to physical errors\n");
  else if (pkts)
    log_Printf(LogLQM, "                   Likely due to transport "
	       "congestion\n");
}