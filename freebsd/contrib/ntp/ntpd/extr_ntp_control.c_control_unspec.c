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
struct recvbuf {int dummy; } ;
struct peer {int dummy; } ;
struct TYPE_2__ {void* status; } ;

/* Variables and functions */
 int /*<<< orphan*/  CERR_BADASSOC ; 
 int /*<<< orphan*/  ctl_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_flushpkt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctlpeerstatus (struct peer*) ; 
 int /*<<< orphan*/  ctlsysstatus () ; 
 struct peer* findpeerbyassoc (scalar_t__) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 scalar_t__ res_associd ; 
 TYPE_1__ rpkt ; 

__attribute__((used)) static void
control_unspec(
	struct recvbuf *rbufp,
	int restrict_mask
	)
{
	struct peer *peer;

	/*
	 * What is an appropriate response to an unspecified op-code?
	 * I return no errors and no data, unless a specified assocation
	 * doesn't exist.
	 */
	if (res_associd) {
		peer = findpeerbyassoc(res_associd);
		if (NULL == peer) {
			ctl_error(CERR_BADASSOC);
			return;
		}
		rpkt.status = htons(ctlpeerstatus(peer));
	} else
		rpkt.status = htons(ctlsysstatus());
	ctl_flushpkt(0);
}