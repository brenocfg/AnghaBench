#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_9__ {scalar_t__ ndo_eflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
#define  ATM_LANE 135 
#define  ATM_LLC 134 
 int /*<<< orphan*/  ATM_OAM_HEC ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
#define  VCI_BCC 133 
#define  VCI_ILMIC 132 
#define  VCI_METAC 131 
#define  VCI_OAMF4EC 130 
#define  VCI_OAMF4SC 129 
#define  VCI_PPC 128 
 int /*<<< orphan*/  atm_llc_print (TYPE_1__*,int /*<<< orphan*/  const*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  lane_print (TYPE_1__*,int /*<<< orphan*/  const*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  oam_print (TYPE_1__*,int /*<<< orphan*/  const*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sig_print (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  snmp_print (TYPE_1__*,int /*<<< orphan*/  const*,scalar_t__) ; 

void
atm_print(netdissect_options *ndo,
          u_int vpi, u_int vci, u_int traftype, const u_char *p, u_int length,
          u_int caplen)
{
	if (ndo->ndo_eflag)
		ND_PRINT((ndo, "VPI:%u VCI:%u ", vpi, vci));

	if (vpi == 0) {
		switch (vci) {

		case VCI_PPC:
			sig_print(ndo, p);
			return;

		case VCI_BCC:
			ND_PRINT((ndo, "broadcast sig: "));
			return;

		case VCI_OAMF4SC: /* fall through */
		case VCI_OAMF4EC:
			oam_print(ndo, p, length, ATM_OAM_HEC);
			return;

		case VCI_METAC:
			ND_PRINT((ndo, "meta: "));
			return;

		case VCI_ILMIC:
			ND_PRINT((ndo, "ilmi: "));
			snmp_print(ndo, p, length);
			return;
		}
	}

	switch (traftype) {

	case ATM_LLC:
	default:
		/*
		 * Assumes traffic is LLC if unknown.
		 */
		atm_llc_print(ndo, p, length, caplen);
		break;

	case ATM_LANE:
		lane_print(ndo, p, length, caplen);
		break;
	}
}