#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int u_int ;
struct TYPE_12__ {scalar_t__ ndo_eflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TTEST (int const) ; 
#define  NLPID_CLNP 135 
#define  NLPID_ESIS 134 
#define  NLPID_IP 133 
#define  NLPID_IP6 132 
#define  NLPID_ISIS 131 
#define  NLPID_NULLNS 130 
#define  NLPID_PPP 129 
#define  NLPID_Q933 128 
 int /*<<< orphan*/  clnp_print (TYPE_1__*,int const*,int) ; 
 int /*<<< orphan*/  esis_print (TYPE_1__*,int const*,int) ; 
 int /*<<< orphan*/  ip6_print (TYPE_1__*,int const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_print (TYPE_1__*,int const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isis_print (TYPE_1__*,int const*,int) ; 
 int /*<<< orphan*/  nlpid_values ; 
 int /*<<< orphan*/  ppp_print (TYPE_1__*,int const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_unknown_data (TYPE_1__*,int const*,char*,int) ; 
 int /*<<< orphan*/  q933_print (TYPE_1__*,int const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int const) ; 

void
isoclns_print(netdissect_options *ndo, const uint8_t *p, u_int length)
{
	if (!ND_TTEST(*p)) { /* enough bytes on the wire ? */
		ND_PRINT((ndo, "|OSI"));
		return;
	}

	if (ndo->ndo_eflag)
		ND_PRINT((ndo, "OSI NLPID %s (0x%02x): ", tok2str(nlpid_values, "Unknown", *p), *p));

	switch (*p) {

	case NLPID_CLNP:
		if (!clnp_print(ndo, p, length))
			print_unknown_data(ndo, p, "\n\t", length);
		break;

	case NLPID_ESIS:
		esis_print(ndo, p, length);
		return;

	case NLPID_ISIS:
		if (!isis_print(ndo, p, length))
			print_unknown_data(ndo, p, "\n\t", length);
		break;

	case NLPID_NULLNS:
		ND_PRINT((ndo, "%slength: %u", ndo->ndo_eflag ? "" : ", ", length));
		break;

	case NLPID_Q933:
		q933_print(ndo, p + 1, length - 1);
		break;

	case NLPID_IP:
		ip_print(ndo, p + 1, length - 1);
		break;

	case NLPID_IP6:
		ip6_print(ndo, p + 1, length - 1);
		break;

	case NLPID_PPP:
		ppp_print(ndo, p + 1, length - 1);
		break;

	default:
		if (!ndo->ndo_eflag)
			ND_PRINT((ndo, "OSI NLPID 0x%02x unknown", *p));
		ND_PRINT((ndo, "%slength: %u", ndo->ndo_eflag ? "" : ", ", length));
		if (length > 1)
			print_unknown_data(ndo, p, "\n\t", length);
		break;
	}
}