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
struct req_pkt {int /*<<< orphan*/  u; int /*<<< orphan*/  err_nitems; } ;
typedef  int /*<<< orphan*/  sockaddr_u ;
typedef  int keyid_t ;
typedef  int /*<<< orphan*/  endpt ;

/* Variables and functions */
 int /*<<< orphan*/  INFO_ERR_FMT ; 
 int /*<<< orphan*/  INFO_ERR_NODATA ; 
 int INFO_NITEMS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INFO_OKAY ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int NTP_MAXKEY ; 
 int /*<<< orphan*/  auth_havekey (int) ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int ntohl (int) ; 
 int /*<<< orphan*/  req_ack (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct req_pkt*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_keyid_checked(
	keyid_t        *into,
	const char     *what,
	sockaddr_u     *srcadr,
	endpt          *inter,
	struct req_pkt *inpkt
	)
{
	keyid_t *pkeyid;
	keyid_t  tmpkey;

	/* restrict ourselves to one item only */
	if (INFO_NITEMS(inpkt->err_nitems) > 1) {
		msyslog(LOG_ERR, "set_keyid_checked[%s]: err_nitems > 1",
			what);
		req_ack(srcadr, inter, inpkt, INFO_ERR_FMT);
		return;
	}

	/* plug the new key from the packet */
	pkeyid = (keyid_t *)&inpkt->u;
	tmpkey = ntohl(*pkeyid);

	/* validate the new key id, claim data error on failure */
	if (tmpkey < 1 || tmpkey > NTP_MAXKEY || !auth_havekey(tmpkey)) {
		msyslog(LOG_ERR, "set_keyid_checked[%s]: invalid key id: %ld",
			what, (long)tmpkey);
		req_ack(srcadr, inter, inpkt, INFO_ERR_NODATA);
		return;
	}

	/* if we arrive here, the key is good -- use it */
	*into = tmpkey;
	req_ack(srcadr, inter, inpkt, INFO_OKAY);
}