#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  rmp_session; } ;
struct TYPE_10__ {int /*<<< orphan*/  rmp_session; } ;
struct TYPE_12__ {int /*<<< orphan*/  rmp_session; } ;
struct rmp_packet {scalar_t__ r_type; TYPE_2__ r_rrpl; TYPE_1__ r_brpl; TYPE_3__ r_rrq; } ;
struct TYPE_13__ {struct rmp_packet rmp; } ;
typedef  TYPE_4__ RMPCONN ;

/* Variables and functions */
 int /*<<< orphan*/  EnetStr (TYPE_4__*) ; 
 TYPE_4__* FindConn (TYPE_4__*) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 scalar_t__ RMP_BOOT_REPL ; 
 int /*<<< orphan*/  RemoveConn (TYPE_4__*) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int
BootDone(RMPCONN *rconn)
{
	RMPCONN *oldconn;
	struct rmp_packet *rpl;

	/*
	 *  If we can't find the connection, ignore the request.
	 */
	if ((oldconn = FindConn(rconn)) == NULL) {
		syslog(LOG_ERR, "BootDone: no existing connection (%s)",
		       EnetStr(rconn));
		return(0);
	}

	rpl = &oldconn->rmp;			/* cache ptr to RMP packet */

	/*
	 *  Make sure Session ID's match.
	 */
	if (ntohs(rconn->rmp.r_rrq.rmp_session) !=
	    ((rpl->r_type == RMP_BOOT_REPL)? ntohs(rpl->r_brpl.rmp_session):
	                                    ntohs(rpl->r_rrpl.rmp_session))) {
		syslog(LOG_ERR, "BootDone: bad session id (%s)",
		       EnetStr(rconn));
		return(0);
	}

	RemoveConn(oldconn);			/* remove connection */

	syslog(LOG_INFO, "%s: boot complete", EnetStr(rconn));

	return(1);
}