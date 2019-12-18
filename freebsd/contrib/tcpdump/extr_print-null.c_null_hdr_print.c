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
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_4__ {int /*<<< orphan*/  ndo_qflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  bsd_af_values ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
null_hdr_print(netdissect_options *ndo, u_int family, u_int length)
{
	if (!ndo->ndo_qflag) {
		ND_PRINT((ndo, "AF %s (%u)",
			tok2str(bsd_af_values,"Unknown",family),family));
	} else {
		ND_PRINT((ndo, "%s",
			tok2str(bsd_af_values,"Unknown AF %u",family)));
	}

	ND_PRINT((ndo, ", length %u: ", length));
}