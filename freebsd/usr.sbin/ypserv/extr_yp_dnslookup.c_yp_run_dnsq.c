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
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int dummy; } ;
struct hostent {char* h_addr; int /*<<< orphan*/  h_length; int /*<<< orphan*/  h_addrtype; } ;
struct circleq_dnsentry {scalar_t__ type; struct circleq_dnsentry* name; int /*<<< orphan*/  addrlen; int /*<<< orphan*/  addrtype; scalar_t__ addr; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  BY_DNS_ID ; 
 int /*<<< orphan*/  MAXPACKET ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct circleq_dnsentry*,int /*<<< orphan*/ ) ; 
 scalar_t__ T_PTR ; 
 struct hostent* __dns_getanswer (char*,int,struct circleq_dnsentry*,scalar_t__) ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (struct circleq_dnsentry*) ; 
 int /*<<< orphan*/  inet_ntoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  links ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse (struct hostent*) ; 
 int /*<<< orphan*/  pending ; 
 int /*<<< orphan*/  qhead ; 
 int recvfrom (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  resfd ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yp_error (char*,...) ; 
 struct circleq_dnsentry* yp_find_dnsqent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yp_prune_dnsq () ; 
 int /*<<< orphan*/  yp_send_dns_reply (struct circleq_dnsentry*,int /*<<< orphan*/ ) ; 

void
yp_run_dnsq(void)
{
	register struct circleq_dnsentry *q;
	char buf[sizeof(HEADER) + MAXPACKET];
	struct sockaddr_in sin;
	socklen_t len;
	int rval;
	HEADER *hptr;
	struct hostent *hent;

	if (debug)
		yp_error("running dns queue");

	bzero(buf, sizeof(buf));

	len = sizeof(struct sockaddr_in);
	rval = recvfrom(resfd, buf, sizeof(buf), 0,
			(struct sockaddr *)&sin, &len);

	if (rval == -1) {
		yp_error("recvfrom failed: %s", strerror(errno));
		return;
	}

	/*
	 * We may have data left in the socket that represents
	 * replies to earlier queries that we don't care about
	 * anymore. If there are no lookups pending or the packet
	 * ID doesn't match any of the queue IDs, just drop it
	 * on the floor.
	 */
	hptr = (HEADER *)&buf;
	if (!pending ||
		(q = yp_find_dnsqent(ntohs(hptr->id), BY_DNS_ID)) == NULL) {
		/* ignore */
		return;
	}

	if (debug)
		yp_error("got dns reply from %s", inet_ntoa(sin.sin_addr));

	hent = __dns_getanswer(buf, rval, q->name, q->type);

	if (hent != NULL) {
		if (q->type == T_PTR) {
			hent->h_addr = (char *)q->addr;
			hent->h_addrtype = q->addrtype;
			hent->h_length = q->addrlen;
		}
	}

	/* Got an answer ready for a client -- send it off. */
	yp_send_dns_reply(q, parse(hent));
	pending--;
	TAILQ_REMOVE(&qhead, q, links);
	free(q->name);
	free(q);

	/* Decrement TTLs on other entries while we're here. */
	yp_prune_dnsq();

	return;
}