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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRACT_32BITS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ND_TCHECK (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  const* parse_wcc_attr (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static const uint32_t *
parse_pre_op_attr(netdissect_options *ndo,
                  const uint32_t *dp, int verbose)
{
	ND_TCHECK(dp[0]);
	if (!EXTRACT_32BITS(&dp[0]))
		return (dp + 1);
	dp++;
	ND_TCHECK2(*dp, 24);
	if (verbose > 1) {
		return parse_wcc_attr(ndo, dp);
	} else {
		/* If not verbose enough, just skip over wcc_attr */
		return (dp + 6);
	}
trunc:
	return (NULL);
}