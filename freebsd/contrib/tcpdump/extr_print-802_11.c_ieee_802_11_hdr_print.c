#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct mgmt_header_t {int /*<<< orphan*/  duration; } ;
struct meshcntl_t {int flags; int /*<<< orphan*/  addr6; int /*<<< orphan*/  addr5; int /*<<< orphan*/  addr4; int /*<<< orphan*/  seq; int /*<<< orphan*/  ttl; } ;
struct TYPE_8__ {scalar_t__ ndo_vflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 scalar_t__ CTRL_PS_POLL ; 
 int /*<<< orphan*/  EXTRACT_LE_16BITS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EXTRACT_LE_32BITS (int /*<<< orphan*/ ) ; 
 scalar_t__ FC_MORE_DATA (int /*<<< orphan*/ ) ; 
 scalar_t__ FC_MORE_FLAG (int /*<<< orphan*/ ) ; 
 scalar_t__ FC_ORDER (int /*<<< orphan*/ ) ; 
 scalar_t__ FC_POWER_MGMT (int /*<<< orphan*/ ) ; 
 scalar_t__ FC_PROTECTED (int /*<<< orphan*/ ) ; 
 scalar_t__ FC_RETRY (int /*<<< orphan*/ ) ; 
 scalar_t__ FC_SUBTYPE (int /*<<< orphan*/ ) ; 
 int FC_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
#define  T_CTRL 130 
#define  T_DATA 129 
#define  T_MGMT 128 
 int /*<<< orphan*/  ctrl_header_print (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  data_header_print (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  etheraddr_string (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mgmt_header_print (TYPE_1__*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void
ieee_802_11_hdr_print(netdissect_options *ndo,
                      uint16_t fc, const u_char *p, u_int hdrlen,
                      u_int meshdrlen)
{
	if (ndo->ndo_vflag) {
		if (FC_MORE_DATA(fc))
			ND_PRINT((ndo, "More Data "));
		if (FC_MORE_FLAG(fc))
			ND_PRINT((ndo, "More Fragments "));
		if (FC_POWER_MGMT(fc))
			ND_PRINT((ndo, "Pwr Mgmt "));
		if (FC_RETRY(fc))
			ND_PRINT((ndo, "Retry "));
		if (FC_ORDER(fc))
			ND_PRINT((ndo, "Strictly Ordered "));
		if (FC_PROTECTED(fc))
			ND_PRINT((ndo, "Protected "));
		if (FC_TYPE(fc) != T_CTRL || FC_SUBTYPE(fc) != CTRL_PS_POLL)
			ND_PRINT((ndo, "%dus ",
			    EXTRACT_LE_16BITS(
			        &((const struct mgmt_header_t *)p)->duration)));
	}
	if (meshdrlen != 0) {
		const struct meshcntl_t *mc =
		    (const struct meshcntl_t *)&p[hdrlen - meshdrlen];
		int ae = mc->flags & 3;

		ND_PRINT((ndo, "MeshData (AE %d TTL %u seq %u", ae, mc->ttl,
		    EXTRACT_LE_32BITS(mc->seq)));
		if (ae > 0)
			ND_PRINT((ndo, " A4:%s", etheraddr_string(ndo, mc->addr4)));
		if (ae > 1)
			ND_PRINT((ndo, " A5:%s", etheraddr_string(ndo, mc->addr5)));
		if (ae > 2)
			ND_PRINT((ndo, " A6:%s", etheraddr_string(ndo, mc->addr6)));
		ND_PRINT((ndo, ") "));
	}

	switch (FC_TYPE(fc)) {
	case T_MGMT:
		mgmt_header_print(ndo, p);
		break;
	case T_CTRL:
		ctrl_header_print(ndo, fc, p);
		break;
	case T_DATA:
		data_header_print(ndo, fc, p);
		break;
	default:
		break;
	}
}