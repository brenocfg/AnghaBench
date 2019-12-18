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
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct igrprte {int dummy; } ;
struct igrphdr {int /*<<< orphan*/  ig_as; int /*<<< orphan*/  ig_ed; int /*<<< orphan*/  ig_vop; int /*<<< orphan*/  ig_nx; int /*<<< orphan*/  ig_ns; int /*<<< orphan*/  ig_ni; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 scalar_t__ EXTRACT_16BITS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IGRP_OP (int /*<<< orphan*/ ) ; 
 scalar_t__ IGRP_RTE_SIZE ; 
 int /*<<< orphan*/  IGRP_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK (struct igrphdr const) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int /*<<< orphan*/  const,scalar_t__) ; 
 int /*<<< orphan*/  igrp_entry_print (int /*<<< orphan*/ *,struct igrprte const*,int,int) ; 
 int /*<<< orphan*/  op2str ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void
igrp_print(netdissect_options *ndo, register const u_char *bp, u_int length)
{
	register const struct igrphdr *hdr;
	register const u_char *cp;
	u_int nint, nsys, next;

	hdr = (const struct igrphdr *)bp;
	cp = (const u_char *)(hdr + 1);
	ND_PRINT((ndo, "igrp:"));

	/* Header */
	ND_TCHECK(*hdr);
	nint = EXTRACT_16BITS(&hdr->ig_ni);
	nsys = EXTRACT_16BITS(&hdr->ig_ns);
	next = EXTRACT_16BITS(&hdr->ig_nx);

	ND_PRINT((ndo, " %s V%d edit=%d AS=%d (%d/%d/%d)",
	    tok2str(op2str, "op-#%d", IGRP_OP(hdr->ig_vop)),
	    IGRP_V(hdr->ig_vop),
	    hdr->ig_ed,
	    EXTRACT_16BITS(&hdr->ig_as),
	    nint,
	    nsys,
	    next));

	length -= sizeof(*hdr);
	while (length >= IGRP_RTE_SIZE) {
		if (nint > 0) {
			ND_TCHECK2(*cp, IGRP_RTE_SIZE);
			igrp_entry_print(ndo, (const struct igrprte *)cp, 1, 0);
			--nint;
		} else if (nsys > 0) {
			ND_TCHECK2(*cp, IGRP_RTE_SIZE);
			igrp_entry_print(ndo, (const struct igrprte *)cp, 0, 0);
			--nsys;
		} else if (next > 0) {
			ND_TCHECK2(*cp, IGRP_RTE_SIZE);
			igrp_entry_print(ndo, (const struct igrprte *)cp, 0, 1);
			--next;
		} else {
			ND_PRINT((ndo, " [extra bytes %d]", length));
			break;
		}
		cp += IGRP_RTE_SIZE;
		length -= IGRP_RTE_SIZE;
	}
	if (nint == 0 && nsys == 0 && next == 0)
		return;
trunc:
	ND_PRINT((ndo, " [|igrp]"));
}