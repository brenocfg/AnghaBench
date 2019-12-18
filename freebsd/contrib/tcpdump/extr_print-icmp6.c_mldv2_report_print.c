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
typedef  int u_char ;
struct in6_addr {int dummy; } ;
struct icmp6_hdr {int /*<<< orphan*/ * icmp6_data16; } ;
struct TYPE_5__ {int ndo_vflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int EXTRACT_16BITS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int const,int) ; 
 int /*<<< orphan*/  ip6addr_string (TYPE_1__*,int const*) ; 
 int /*<<< orphan*/  mldv2report2str ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int const) ; 

__attribute__((used)) static void
mldv2_report_print(netdissect_options *ndo, const u_char *bp, u_int len)
{
    const struct icmp6_hdr *icp = (const struct icmp6_hdr *) bp;
    u_int group, nsrcs, ngroups;
    u_int i, j;

    /* Minimum len is 8 */
    if (len < 8) {
            ND_PRINT((ndo," [invalid len %d]", len));
            return;
    }

    ND_TCHECK(icp->icmp6_data16[1]);
    ngroups = EXTRACT_16BITS(&icp->icmp6_data16[1]);
    ND_PRINT((ndo,", %d group record(s)", ngroups));
    if (ndo->ndo_vflag > 0) {
	/* Print the group records */
	group = 8;
        for (i = 0; i < ngroups; i++) {
	    /* type(1) + auxlen(1) + numsrc(2) + grp(16) */
	    if (len < group + 20) {
                    ND_PRINT((ndo," [invalid number of groups]"));
                    return;
	    }
            ND_TCHECK2(bp[group + 4], sizeof(struct in6_addr));
            ND_PRINT((ndo," [gaddr %s", ip6addr_string(ndo, &bp[group + 4])));
	    ND_PRINT((ndo," %s", tok2str(mldv2report2str, " [v2-report-#%d]",
                                         bp[group])));
            nsrcs = (bp[group + 2] << 8) + bp[group + 3];
	    /* Check the number of sources and print them */
	    if (len < group + 20 + (nsrcs * sizeof(struct in6_addr))) {
                    ND_PRINT((ndo," [invalid number of sources %d]", nsrcs));
                    return;
	    }
            if (ndo->ndo_vflag == 1)
                    ND_PRINT((ndo,", %d source(s)", nsrcs));
            else {
		/* Print the sources */
                    ND_PRINT((ndo," {"));
                for (j = 0; j < nsrcs; j++) {
                    ND_TCHECK2(bp[group + 20 + j * sizeof(struct in6_addr)],
                            sizeof(struct in6_addr));
		    ND_PRINT((ndo," %s", ip6addr_string(ndo, &bp[group + 20 + j * sizeof(struct in6_addr)])));
		}
                ND_PRINT((ndo," }"));
            }
	    /* Next group record */
            group += 20 + nsrcs * sizeof(struct in6_addr);
	    ND_PRINT((ndo,"]"));
        }
    }
    return;
trunc:
    ND_PRINT((ndo,"[|icmp6]"));
    return;
}