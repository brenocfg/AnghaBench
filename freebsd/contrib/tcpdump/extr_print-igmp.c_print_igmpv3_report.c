#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_5__ {int ndo_vflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int EXTRACT_16BITS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  igmpv3report2str ; 
 int /*<<< orphan*/  ipaddr_string (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  tstr ; 

__attribute__((used)) static void
print_igmpv3_report(netdissect_options *ndo,
                    register const u_char *bp, register u_int len)
{
    u_int group, nsrcs, ngroups;
    register u_int i, j;

    /* Minimum len is 16, and should be a multiple of 4 */
    if (len < 16 || len & 0x03) {
	ND_PRINT((ndo, " [invalid len %d]", len));
	return;
    }
    ND_TCHECK2(bp[6], 2);
    ngroups = EXTRACT_16BITS(&bp[6]);
    ND_PRINT((ndo, ", %d group record(s)", ngroups));
    if (ndo->ndo_vflag > 0) {
	/* Print the group records */
	group = 8;
        for (i=0; i<ngroups; i++) {
	    if (len < group+8) {
		ND_PRINT((ndo, " [invalid number of groups]"));
		return;
	    }
	    ND_TCHECK2(bp[group+4], 4);
            ND_PRINT((ndo, " [gaddr %s", ipaddr_string(ndo, &bp[group+4])));
	    ND_PRINT((ndo, " %s", tok2str(igmpv3report2str, " [v3-report-#%d]",
								bp[group])));
            nsrcs = EXTRACT_16BITS(&bp[group+2]);
	    /* Check the number of sources and print them */
	    if (len < group+8+(nsrcs<<2)) {
		ND_PRINT((ndo, " [invalid number of sources %d]", nsrcs));
		return;
	    }
            if (ndo->ndo_vflag == 1)
                ND_PRINT((ndo, ", %d source(s)", nsrcs));
            else {
		/* Print the sources */
                ND_PRINT((ndo, " {"));
                for (j=0; j<nsrcs; j++) {
		    ND_TCHECK2(bp[group+8+(j<<2)], 4);
		    ND_PRINT((ndo, " %s", ipaddr_string(ndo, &bp[group+8+(j<<2)])));
		}
                ND_PRINT((ndo, " }"));
            }
	    /* Next group record */
            group += 8 + (nsrcs << 2);
	    ND_PRINT((ndo, "]"));
        }
    }
    return;
trunc:
    ND_PRINT((ndo, "%s", tstr));
}