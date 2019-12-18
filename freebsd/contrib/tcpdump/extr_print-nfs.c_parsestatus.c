#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  ndo_qflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int EXTRACT_32BITS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK (int /*<<< orphan*/  const) ; 
 int nfserr ; 
 int /*<<< orphan*/  status2str ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static const uint32_t *
parsestatus(netdissect_options *ndo,
            const uint32_t *dp, int *er)
{
	int errnum;

	ND_TCHECK(dp[0]);

	errnum = EXTRACT_32BITS(&dp[0]);
	if (er)
		*er = errnum;
	if (errnum != 0) {
		if (!ndo->ndo_qflag)
			ND_PRINT((ndo, " ERROR: %s",
			    tok2str(status2str, "unk %d", errnum)));
		nfserr = 1;
	}
	return (dp + 1);
trunc:
	return NULL;
}