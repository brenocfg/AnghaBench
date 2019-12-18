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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRACT_32BITS (int /*<<< orphan*/  const*) ; 
#define  ISIS_SUBTLV_EXTD_IP_REACH_ADMIN_TAG32 130 
#define  ISIS_SUBTLV_EXTD_IP_REACH_ADMIN_TAG64 129 
#define  ISIS_SUBTLV_EXTD_IP_REACH_MGMT_PREFIX_COLOR 128 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  isis_ext_ip_reach_subtlv_values ; 
 int /*<<< orphan*/  print_unknown_data (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,char*,int) ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  tstr ; 

__attribute__((used)) static int
isis_print_ip_reach_subtlv(netdissect_options *ndo,
                           const uint8_t *tptr, int subt, int subl,
                           const char *ident)
{
    /* first lets see if we know the subTLVs name*/
    ND_PRINT((ndo, "%s%s subTLV #%u, length: %u",
              ident, tok2str(isis_ext_ip_reach_subtlv_values, "unknown", subt),
              subt, subl));

    ND_TCHECK2(*tptr,subl);

    switch(subt) {
    case ISIS_SUBTLV_EXTD_IP_REACH_MGMT_PREFIX_COLOR: /* fall through */
    case ISIS_SUBTLV_EXTD_IP_REACH_ADMIN_TAG32:
        while (subl >= 4) {
	    ND_PRINT((ndo, ", 0x%08x (=%u)",
		   EXTRACT_32BITS(tptr),
		   EXTRACT_32BITS(tptr)));
	    tptr+=4;
	    subl-=4;
	}
	break;
    case ISIS_SUBTLV_EXTD_IP_REACH_ADMIN_TAG64:
        while (subl >= 8) {
	    ND_PRINT((ndo, ", 0x%08x%08x",
		   EXTRACT_32BITS(tptr),
		   EXTRACT_32BITS(tptr+4)));
	    tptr+=8;
	    subl-=8;
	}
	break;
    default:
	if (!print_unknown_data(ndo, tptr, "\n\t\t    ", subl))
	  return(0);
	break;
    }
    return(1);

trunc:
    ND_PRINT((ndo, "%s", ident));
    ND_PRINT((ndo, "%s", tstr));
    return(0);
}