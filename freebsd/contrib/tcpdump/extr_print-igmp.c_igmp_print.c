#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
typedef  int u_char ;
struct cksum_vec {int const* ptr; int len; } ;
struct TYPE_11__ {scalar_t__ ndo_vflag; scalar_t__ ndo_qflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRACT_16BITS (int const*) ; 
 int /*<<< orphan*/  EXTRACT_32BITS (int const*) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK (int const) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int const,int) ; 
 scalar_t__ ND_TTEST2 (int const,int) ; 
 int /*<<< orphan*/  dvmrp_print (TYPE_1__*,int const*,int) ; 
 scalar_t__ in_cksum (struct cksum_vec*,int) ; 
 int /*<<< orphan*/  ipaddr_string (TYPE_1__*,int const*) ; 
 int /*<<< orphan*/  pimv1_print (TYPE_1__*,int const*,int) ; 
 int /*<<< orphan*/  print_igmpv3_query (TYPE_1__*,int const*,int) ; 
 int /*<<< orphan*/  print_igmpv3_report (TYPE_1__*,int const*,int) ; 
 int /*<<< orphan*/  print_mresp (TYPE_1__*,int const*,int) ; 
 int /*<<< orphan*/  print_mtrace (TYPE_1__*,int const*,int) ; 
 int /*<<< orphan*/  tstr ; 

void
igmp_print(netdissect_options *ndo,
           register const u_char *bp, register u_int len)
{
    struct cksum_vec vec[1];

    if (ndo->ndo_qflag) {
        ND_PRINT((ndo, "igmp"));
        return;
    }

    ND_TCHECK(bp[0]);
    switch (bp[0]) {
    case 0x11:
        ND_PRINT((ndo, "igmp query"));
	if (len >= 12)
	    print_igmpv3_query(ndo, bp, len);
	else {
            ND_TCHECK(bp[1]);
	    if (bp[1]) {
		ND_PRINT((ndo, " v2"));
		if (bp[1] != 100)
		    ND_PRINT((ndo, " [max resp time %d]", bp[1]));
	    } else
		ND_PRINT((ndo, " v1"));
            ND_TCHECK2(bp[4], 4);
	    if (EXTRACT_32BITS(&bp[4]))
                ND_PRINT((ndo, " [gaddr %s]", ipaddr_string(ndo, &bp[4])));
            if (len != 8)
                ND_PRINT((ndo, " [len %d]", len));
	}
        break;
    case 0x12:
        ND_TCHECK2(bp[4], 4);
        ND_PRINT((ndo, "igmp v1 report %s", ipaddr_string(ndo, &bp[4])));
        if (len != 8)
            ND_PRINT((ndo, " [len %d]", len));
        break;
    case 0x16:
        ND_TCHECK2(bp[4], 4);
        ND_PRINT((ndo, "igmp v2 report %s", ipaddr_string(ndo, &bp[4])));
        break;
    case 0x22:
        ND_PRINT((ndo, "igmp v3 report"));
	print_igmpv3_report(ndo, bp, len);
        break;
    case 0x17:
        ND_TCHECK2(bp[4], 4);
        ND_PRINT((ndo, "igmp leave %s", ipaddr_string(ndo, &bp[4])));
        break;
    case 0x13:
        ND_PRINT((ndo, "igmp dvmrp"));
        if (len < 8)
            ND_PRINT((ndo, " [len %d]", len));
        else
            dvmrp_print(ndo, bp, len);
        break;
    case 0x14:
        ND_PRINT((ndo, "igmp pimv1"));
        pimv1_print(ndo, bp, len);
        break;
    case 0x1e:
        print_mresp(ndo, bp, len);
        break;
    case 0x1f:
        print_mtrace(ndo, bp, len);
        break;
    default:
        ND_PRINT((ndo, "igmp-%d", bp[0]));
        break;
    }

    if (ndo->ndo_vflag && len >= 4 && ND_TTEST2(bp[0], len)) {
        /* Check the IGMP checksum */
        vec[0].ptr = bp;
        vec[0].len = len;
        if (in_cksum(vec, 1))
            ND_PRINT((ndo, " bad igmp cksum %x!", EXTRACT_16BITS(&bp[2])));
    }
    return;
trunc:
    ND_PRINT((ndo, "%s", tstr));
}