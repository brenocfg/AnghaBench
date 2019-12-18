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
struct eap_sm {scalar_t__ reqId; scalar_t__ lastId; int /*<<< orphan*/  last_sha1; int /*<<< orphan*/  req_sha1; scalar_t__ workaround; scalar_t__ rxReq; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int eap_peer_req_is_duplicate(struct eap_sm *sm)
{
	int duplicate;

	duplicate = (sm->reqId == sm->lastId) && sm->rxReq;
	if (sm->workaround && duplicate &&
	    os_memcmp(sm->req_sha1, sm->last_sha1, 20) != 0) {
		/*
		 * RFC 4137 uses (reqId == lastId) as the only verification for
		 * duplicate EAP requests. However, this misses cases where the
		 * AS is incorrectly using the same id again; and
		 * unfortunately, such implementations exist. Use SHA1 hash as
		 * an extra verification for the packets being duplicate to
		 * workaround these issues.
		 */
		wpa_printf(MSG_DEBUG, "EAP: AS used the same Id again, but "
			   "EAP packets were not identical");
		wpa_printf(MSG_DEBUG, "EAP: workaround - assume this is not a "
			   "duplicate packet");
		duplicate = 0;
	}

	return duplicate;
}