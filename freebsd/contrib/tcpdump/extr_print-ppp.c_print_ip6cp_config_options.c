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
 int /*<<< orphan*/  EXTRACT_16BITS (int const*) ; 
#define  IP6CP_IFID 128 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int const,int) ; 
 int /*<<< orphan*/  ip6cpopt_values ; 
 int /*<<< orphan*/  print_unknown_data (TYPE_1__*,int const*,char*,int) ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
print_ip6cp_config_options(netdissect_options *ndo,
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
		       tok2str(ip6cpopt_values,"unknown",opt),
		       opt,
		       len));
		return 0;
	}

	ND_PRINT((ndo, "\n\t  %s Option (0x%02x), length %u",
	       tok2str(ip6cpopt_values,"unknown",opt),
	       opt,
	       len));

	switch (opt) {
	case IP6CP_IFID:
		if (len != 10) {
			ND_PRINT((ndo, " (length bogus, should be = 10)"));
			return len;
		}
		ND_TCHECK2(*(p + 2), 8);
		ND_PRINT((ndo, ": %04x:%04x:%04x:%04x",
		       EXTRACT_16BITS(p + 2),
		       EXTRACT_16BITS(p + 4),
		       EXTRACT_16BITS(p + 6),
		       EXTRACT_16BITS(p + 8)));
		break;
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
	ND_PRINT((ndo, "[|ip6cp]"));
	return 0;
}