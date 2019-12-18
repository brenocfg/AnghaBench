#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_8__ {int ndo_vflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRACT_32BITS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/ * parse_post_op_attr (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/ * parse_wcc_data (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/ * parsefh (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/ * parsestatus (TYPE_1__*,int /*<<< orphan*/  const*,int*) ; 

__attribute__((used)) static const uint32_t *
parsecreateopres(netdissect_options *ndo,
                 const uint32_t *dp, int verbose)
{
	int er;

	if (!(dp = parsestatus(ndo, dp, &er)))
		return (0);
	if (er)
		dp = parse_wcc_data(ndo, dp, verbose);
	else {
		ND_TCHECK(dp[0]);
		if (!EXTRACT_32BITS(&dp[0]))
			return (dp + 1);
		dp++;
		if (!(dp = parsefh(ndo, dp, 1)))
			return (0);
		if (verbose) {
			if (!(dp = parse_post_op_attr(ndo, dp, verbose)))
				return (0);
			if (ndo->ndo_vflag > 1) {
				ND_PRINT((ndo, " dir attr:"));
				dp = parse_wcc_data(ndo, dp, verbose);
			}
		}
	}
	return (dp);
trunc:
	return (NULL);
}