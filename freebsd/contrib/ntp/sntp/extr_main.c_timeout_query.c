#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sockaddr_u ;
struct TYPE_5__ {TYPE_1__* dctx; int /*<<< orphan*/  addr; int /*<<< orphan*/  done; } ;
typedef  TYPE_2__ sent_pkt ;
struct TYPE_4__ {int flags; int /*<<< orphan*/  name; } ;

/* Variables and functions */
#define  CTX_BCST 129 
#define  CTX_UCST 128 
 int CTX_xCST ; 
 int /*<<< orphan*/  INSIST (int) ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  dec_pending_ntp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hostnameaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  response_timeout ; 

void timeout_query(
	sent_pkt *	spkt
	)
{
	sockaddr_u *	server;
	char		xcst;


	switch (spkt->dctx->flags & CTX_xCST) {
	    case CTX_BCST:
		xcst = 'B';
		break;

	    case CTX_UCST:
		xcst = 'U';
		break;

	    default:
		INSIST(!"spkt->dctx->flags neither UCST nor BCST");
		break;
	}
	spkt->done = TRUE;
	server = &spkt->addr;
	msyslog(LOG_INFO, "%s no %cCST response after %d seconds",
		hostnameaddr(spkt->dctx->name, server), xcst,
		response_timeout);
	dec_pending_ntp(spkt->dctx->name, server);
	return;
}