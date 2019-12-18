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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u_int ;
struct TYPE_2__ {int /*<<< orphan*/  cb_cred; } ;
struct sunrpc_msg {TYPE_1__ rm_call; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int EXTRACT_32BITS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ND_TCHECK (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const uint32_t *
parsereq(netdissect_options *ndo,
         register const struct sunrpc_msg *rp, register u_int length)
{
	register const uint32_t *dp;
	register u_int len;

	/*
	 * find the start of the req data (if we captured it)
	 */
	dp = (const uint32_t *)&rp->rm_call.cb_cred;
	ND_TCHECK(dp[1]);
	len = EXTRACT_32BITS(&dp[1]);
	if (len < length) {
		dp += (len + (2 * sizeof(*dp) + 3)) / sizeof(*dp);
		ND_TCHECK(dp[1]);
		len = EXTRACT_32BITS(&dp[1]);
		if (len < length) {
			dp += (len + (2 * sizeof(*dp) + 3)) / sizeof(*dp);
			ND_TCHECK2(dp[0], 0);
			return (dp);
		}
	}
trunc:
	return (NULL);
}