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
typedef  int u_char ;
struct TYPE_5__ {int ndo_vflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
#define  CCPOPT_BSDCOMP 142 
#define  CCPOPT_DEC 141 
#define  CCPOPT_DEFLATE 140 
#define  CCPOPT_GFZA 139 
#define  CCPOPT_HPPPC 138 
#define  CCPOPT_LZSDCP 137 
#define  CCPOPT_MPPC 136 
#define  CCPOPT_MVRCA 135 
#define  CCPOPT_OUI 134 
#define  CCPOPT_PJUMP 133 
#define  CCPOPT_PRED1 132 
#define  CCPOPT_PRED2 131 
#define  CCPOPT_RESV 130 
#define  CCPOPT_STACLZS 129 
#define  CCPOPT_V42BIS 128 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK (int const) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int const,int) ; 
 int /*<<< orphan*/  ccpconfopts_values ; 
 int /*<<< orphan*/  print_unknown_data (TYPE_1__*,int const*,char*,int) ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
print_ccp_config_options(netdissect_options *ndo,
                         const u_char *p, int length)
{
	int len, opt;

	if (length < 2)
		return 0;
	ND_TCHECK2(*p, 2);
	len = p[1];
	opt = p[0];
	if (length < len)
		return 0;
	if (len < 2) {
		ND_PRINT((ndo, "\n\t  %s Option (0x%02x), length %u (length bogus, should be >= 2)",
		          tok2str(ccpconfopts_values, "Unknown", opt),
		          opt,
		          len));
		return 0;
	}

	ND_PRINT((ndo, "\n\t  %s Option (0x%02x), length %u",
	          tok2str(ccpconfopts_values, "Unknown", opt),
	          opt,
	          len));

	switch (opt) {
	case CCPOPT_BSDCOMP:
		if (len < 3) {
			ND_PRINT((ndo, " (length bogus, should be >= 3)"));
			return len;
		}
		ND_TCHECK(p[2]);
		ND_PRINT((ndo, ": Version: %u, Dictionary Bits: %u",
			p[2] >> 5, p[2] & 0x1f));
		break;
	case CCPOPT_MVRCA:
		if (len < 4) {
			ND_PRINT((ndo, " (length bogus, should be >= 4)"));
			return len;
		}
		ND_TCHECK(p[3]);
		ND_PRINT((ndo, ": Features: %u, PxP: %s, History: %u, #CTX-ID: %u",
				(p[2] & 0xc0) >> 6,
				(p[2] & 0x20) ? "Enabled" : "Disabled",
				p[2] & 0x1f, p[3]));
		break;
	case CCPOPT_DEFLATE:
		if (len < 4) {
			ND_PRINT((ndo, " (length bogus, should be >= 4)"));
			return len;
		}
		ND_TCHECK(p[3]);
		ND_PRINT((ndo, ": Window: %uK, Method: %s (0x%x), MBZ: %u, CHK: %u",
			(p[2] & 0xf0) >> 4,
			((p[2] & 0x0f) == 8) ? "zlib" : "unknown",
			p[2] & 0x0f, (p[3] & 0xfc) >> 2, p[3] & 0x03));
		break;

/* XXX: to be supported */
#if 0
	case CCPOPT_OUI:
	case CCPOPT_PRED1:
	case CCPOPT_PRED2:
	case CCPOPT_PJUMP:
	case CCPOPT_HPPPC:
	case CCPOPT_STACLZS:
	case CCPOPT_MPPC:
	case CCPOPT_GFZA:
	case CCPOPT_V42BIS:
	case CCPOPT_LZSDCP:
	case CCPOPT_DEC:
	case CCPOPT_RESV:
		break;
#endif
	default:
		/*
		 * Unknown option; dump it as raw bytes now if we're
		 * not going to do so below.
		 */
		if (ndo->ndo_vflag < 2)
			print_unknown_data(ndo, &p[2], "\n\t    ", len - 2);
		break;
	}
	if (ndo->ndo_vflag > 1)
		print_unknown_data(ndo, &p[2], "\n\t    ", len - 2); /* exclude TLV header */

	return len;

trunc:
	ND_PRINT((ndo, "[|ccp]"));
	return 0;
}