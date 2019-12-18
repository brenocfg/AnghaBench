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
typedef  int u_int ;
struct pkt_rreq {int dummy; } ;
struct pkt_rrep {int dummy; } ;
struct pkt_preq {int dummy; } ;
struct pkt_prep {int dummy; } ;
struct pkt_id {int dummy; } ;
struct pkt_hdr {int ph_type; scalar_t__ ph_flags; } ;
struct pkt_dop {int dummy; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TTEST (struct pkt_hdr const) ; 
#define  PT_DRAWOP 134 
#define  PT_ID 133 
#define  PT_KILL 132 
#define  PT_PREP 131 
#define  PT_PREQ 130 
#define  PT_RREP 129 
#define  PT_RREQ 128 
 int /*<<< orphan*/  tstr ; 
 int /*<<< orphan*/  wb_drawop (int /*<<< orphan*/ *,struct pkt_dop const*,int) ; 
 int /*<<< orphan*/  wb_id (int /*<<< orphan*/ *,struct pkt_id const*,int) ; 
 int /*<<< orphan*/  wb_prep (int /*<<< orphan*/ *,struct pkt_prep const*,int) ; 
 int /*<<< orphan*/  wb_preq (int /*<<< orphan*/ *,struct pkt_preq const*,int) ; 
 int /*<<< orphan*/  wb_rrep (int /*<<< orphan*/ *,struct pkt_rrep const*,int) ; 
 int /*<<< orphan*/  wb_rreq (int /*<<< orphan*/ *,struct pkt_rreq const*,int) ; 

void
wb_print(netdissect_options *ndo,
         register const void *hdr, register u_int len)
{
	register const struct pkt_hdr *ph;

	ph = (const struct pkt_hdr *)hdr;
	if (len < sizeof(*ph) || !ND_TTEST(*ph)) {
		ND_PRINT((ndo, "%s", tstr));
		return;
	}
	len -= sizeof(*ph);

	if (ph->ph_flags)
		ND_PRINT((ndo, "*"));
	switch (ph->ph_type) {

	case PT_KILL:
		ND_PRINT((ndo, " wb-kill"));
		return;

	case PT_ID:
		if (wb_id(ndo, (const struct pkt_id *)(ph + 1), len) >= 0)
			return;
		ND_PRINT((ndo, "%s", tstr));
		break;

	case PT_RREQ:
		if (wb_rreq(ndo, (const struct pkt_rreq *)(ph + 1), len) >= 0)
			return;
		ND_PRINT((ndo, "%s", tstr));
		break;

	case PT_RREP:
		if (wb_rrep(ndo, (const struct pkt_rrep *)(ph + 1), len) >= 0)
			return;
		ND_PRINT((ndo, "%s", tstr));
		break;

	case PT_DRAWOP:
		if (wb_drawop(ndo, (const struct pkt_dop *)(ph + 1), len) >= 0)
			return;
		ND_PRINT((ndo, "%s", tstr));
		break;

	case PT_PREQ:
		if (wb_preq(ndo, (const struct pkt_preq *)(ph + 1), len) >= 0)
			return;
		ND_PRINT((ndo, "%s", tstr));
		break;

	case PT_PREP:
		if (wb_prep(ndo, (const struct pkt_prep *)(ph + 1), len) >= 0)
			return;
		ND_PRINT((ndo, "%s", tstr));
		break;

	default:
		ND_PRINT((ndo, " wb-%d!", ph->ph_type));
		return;
	}
}