#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {scalar_t__ ndo_vflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/ * parse_post_op_attr (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/ * parsestatus (TYPE_1__*,int /*<<< orphan*/  const*,int*) ; 

__attribute__((used)) static const uint32_t *
parsev3rddirres(netdissect_options *ndo,
                const uint32_t *dp, int verbose)
{
	int er;

	if (!(dp = parsestatus(ndo, dp, &er)))
		return (0);
	if (ndo->ndo_vflag)
		ND_PRINT((ndo, " POST:"));
	if (!(dp = parse_post_op_attr(ndo, dp, verbose)))
		return (0);
	if (er)
		return dp;
	if (ndo->ndo_vflag) {
		ND_TCHECK(dp[1]);
		ND_PRINT((ndo, " verf %08x%08x", dp[0], dp[1]));
		dp += 2;
	}
	return dp;
trunc:
	return (NULL);
}