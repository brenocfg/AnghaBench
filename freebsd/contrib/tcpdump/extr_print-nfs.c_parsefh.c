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
typedef  int u_int ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int EXTRACT_32BITS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ND_TCHECK (int /*<<< orphan*/  const) ; 
 scalar_t__ ND_TTEST2 (int /*<<< orphan*/  const,int) ; 
 int NFSX_V2FH ; 
 int /*<<< orphan*/  nfs_printfh (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static const uint32_t *
parsefh(netdissect_options *ndo,
        register const uint32_t *dp, int v3)
{
	u_int len;

	if (v3) {
		ND_TCHECK(dp[0]);
		len = EXTRACT_32BITS(dp) / 4;
		dp++;
	} else
		len = NFSX_V2FH / 4;

	if (ND_TTEST2(*dp, len * sizeof(*dp))) {
		nfs_printfh(ndo, dp, len);
		return (dp + len);
	}
trunc:
	return (NULL);
}