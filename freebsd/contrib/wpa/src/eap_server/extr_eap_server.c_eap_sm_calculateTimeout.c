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
struct eap_sm {scalar_t__ try_initiate_reauth; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int eap_sm_calculateTimeout(struct eap_sm *sm, int retransCount,
				   int eapSRTT, int eapRTTVAR,
				   int methodTimeout)
{
	int rto, i;

	if (sm->try_initiate_reauth) {
		wpa_printf(MSG_DEBUG,
			   "EAP: retransmit timeout 1 second for EAP-Initiate-Re-auth-Start");
		return 1;
	}

	if (methodTimeout) {
		/*
		 * EAP method (either internal or through AAA server, provided
		 * timeout hint. Use that as-is as a timeout for retransmitting
		 * the EAP request if no response is received.
		 */
		wpa_printf(MSG_DEBUG, "EAP: retransmit timeout %d seconds "
			   "(from EAP method hint)", methodTimeout);
		return methodTimeout;
	}

	/*
	 * RFC 3748 recommends algorithms described in RFC 2988 for estimation
	 * of the retransmission timeout. This should be implemented once
	 * round-trip time measurements are available. For nowm a simple
	 * backoff mechanism is used instead if there are no EAP method
	 * specific hints.
	 *
	 * SRTT = smoothed round-trip time
	 * RTTVAR = round-trip time variation
	 * RTO = retransmission timeout
	 */

	/*
	 * RFC 2988, 2.1: before RTT measurement, set RTO to 3 seconds for
	 * initial retransmission and then double the RTO to provide back off
	 * per 5.5. Limit the maximum RTO to 20 seconds per RFC 3748, 4.3
	 * modified RTOmax.
	 */
	rto = 3;
	for (i = 0; i < retransCount; i++) {
		rto *= 2;
		if (rto >= 20) {
			rto = 20;
			break;
		}
	}

	wpa_printf(MSG_DEBUG, "EAP: retransmit timeout %d seconds "
		   "(from dynamic back off; retransCount=%d)",
		   rto, retransCount);

	return rto;
}