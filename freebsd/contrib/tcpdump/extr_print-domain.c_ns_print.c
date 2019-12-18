#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  u_short ;
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_18__ {int ndo_vflag; int /*<<< orphan*/  const* ndo_snapend; } ;
typedef  TYPE_1__ netdissect_options ;
struct TYPE_19__ {int /*<<< orphan*/  const id; int /*<<< orphan*/  const qdcount; int /*<<< orphan*/  const arcount; int /*<<< orphan*/  const nscount; int /*<<< orphan*/  const ancount; } ;
typedef  TYPE_2__ HEADER ;

/* Variables and functions */
 scalar_t__ DNS_AA (TYPE_2__ const*) ; 
 scalar_t__ DNS_AD (TYPE_2__ const*) ; 
 scalar_t__ DNS_CD (TYPE_2__ const*) ; 
 size_t DNS_OPCODE (TYPE_2__ const*) ; 
 scalar_t__ DNS_QR (TYPE_2__ const*) ; 
 scalar_t__ DNS_RA (TYPE_2__ const*) ; 
 size_t DNS_RCODE (TYPE_2__ const*) ; 
 scalar_t__ DNS_RD (TYPE_2__ const*) ; 
 scalar_t__ DNS_TC (TYPE_2__ const*) ; 
 int EXTRACT_16BITS (int /*<<< orphan*/  const*) ; 
 size_t IQUERY ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK (TYPE_2__ const) ; 
 int /*<<< orphan*/ * ns_nskip (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * ns_ops ; 
 int /*<<< orphan*/ * ns_qprint (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/ * ns_resp ; 
 int /*<<< orphan*/ * ns_rprint (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 

void
ns_print(netdissect_options *ndo,
         register const u_char *bp, u_int length, int is_mdns)
{
	register const HEADER *np;
	register int qdcount, ancount, nscount, arcount;
	register const u_char *cp;
	uint16_t b2;

	np = (const HEADER *)bp;
	ND_TCHECK(*np);
	/* get the byte-order right */
	qdcount = EXTRACT_16BITS(&np->qdcount);
	ancount = EXTRACT_16BITS(&np->ancount);
	nscount = EXTRACT_16BITS(&np->nscount);
	arcount = EXTRACT_16BITS(&np->arcount);

	if (DNS_QR(np)) {
		/* this is a response */
		ND_PRINT((ndo, "%d%s%s%s%s%s%s",
			EXTRACT_16BITS(&np->id),
			ns_ops[DNS_OPCODE(np)],
			ns_resp[DNS_RCODE(np)],
			DNS_AA(np)? "*" : "",
			DNS_RA(np)? "" : "-",
			DNS_TC(np)? "|" : "",
			DNS_AD(np)? "$" : ""));

		if (qdcount != 1)
			ND_PRINT((ndo, " [%dq]", qdcount));
		/* Print QUESTION section on -vv */
		cp = (const u_char *)(np + 1);
		while (qdcount--) {
			if (qdcount < EXTRACT_16BITS(&np->qdcount) - 1)
				ND_PRINT((ndo, ","));
			if (ndo->ndo_vflag > 1) {
				ND_PRINT((ndo, " q:"));
				if ((cp = ns_qprint(ndo, cp, bp, is_mdns)) == NULL)
					goto trunc;
			} else {
				if ((cp = ns_nskip(ndo, cp)) == NULL)
					goto trunc;
				cp += 4;	/* skip QTYPE and QCLASS */
			}
		}
		ND_PRINT((ndo, " %d/%d/%d", ancount, nscount, arcount));
		if (ancount--) {
			if ((cp = ns_rprint(ndo, cp, bp, is_mdns)) == NULL)
				goto trunc;
			while (cp < ndo->ndo_snapend && ancount--) {
				ND_PRINT((ndo, ","));
				if ((cp = ns_rprint(ndo, cp, bp, is_mdns)) == NULL)
					goto trunc;
			}
		}
		if (ancount > 0)
			goto trunc;
		/* Print NS and AR sections on -vv */
		if (ndo->ndo_vflag > 1) {
			if (cp < ndo->ndo_snapend && nscount--) {
				ND_PRINT((ndo, " ns:"));
				if ((cp = ns_rprint(ndo, cp, bp, is_mdns)) == NULL)
					goto trunc;
				while (cp < ndo->ndo_snapend && nscount--) {
					ND_PRINT((ndo, ","));
					if ((cp = ns_rprint(ndo, cp, bp, is_mdns)) == NULL)
						goto trunc;
				}
			}
			if (nscount > 0)
				goto trunc;
			if (cp < ndo->ndo_snapend && arcount--) {
				ND_PRINT((ndo, " ar:"));
				if ((cp = ns_rprint(ndo, cp, bp, is_mdns)) == NULL)
					goto trunc;
				while (cp < ndo->ndo_snapend && arcount--) {
					ND_PRINT((ndo, ","));
					if ((cp = ns_rprint(ndo, cp, bp, is_mdns)) == NULL)
						goto trunc;
				}
			}
			if (arcount > 0)
				goto trunc;
		}
	}
	else {
		/* this is a request */
		ND_PRINT((ndo, "%d%s%s%s", EXTRACT_16BITS(&np->id), ns_ops[DNS_OPCODE(np)],
		    DNS_RD(np) ? "+" : "",
		    DNS_CD(np) ? "%" : ""));

		/* any weirdness? */
		b2 = EXTRACT_16BITS(((const u_short *)np)+1);
		if (b2 & 0x6cf)
			ND_PRINT((ndo, " [b2&3=0x%x]", b2));

		if (DNS_OPCODE(np) == IQUERY) {
			if (qdcount)
				ND_PRINT((ndo, " [%dq]", qdcount));
			if (ancount != 1)
				ND_PRINT((ndo, " [%da]", ancount));
		}
		else {
			if (ancount)
				ND_PRINT((ndo, " [%da]", ancount));
			if (qdcount != 1)
				ND_PRINT((ndo, " [%dq]", qdcount));
		}
		if (nscount)
			ND_PRINT((ndo, " [%dn]", nscount));
		if (arcount)
			ND_PRINT((ndo, " [%dau]", arcount));

		cp = (const u_char *)(np + 1);
		if (qdcount--) {
			cp = ns_qprint(ndo, cp, (const u_char *)np, is_mdns);
			if (!cp)
				goto trunc;
			while (cp < ndo->ndo_snapend && qdcount--) {
				cp = ns_qprint(ndo, (const u_char *)cp,
					       (const u_char *)np,
					       is_mdns);
				if (!cp)
					goto trunc;
			}
		}
		if (qdcount > 0)
			goto trunc;

		/* Print remaining sections on -vv */
		if (ndo->ndo_vflag > 1) {
			if (ancount--) {
				if ((cp = ns_rprint(ndo, cp, bp, is_mdns)) == NULL)
					goto trunc;
				while (cp < ndo->ndo_snapend && ancount--) {
					ND_PRINT((ndo, ","));
					if ((cp = ns_rprint(ndo, cp, bp, is_mdns)) == NULL)
						goto trunc;
				}
			}
			if (ancount > 0)
				goto trunc;
			if (cp < ndo->ndo_snapend && nscount--) {
				ND_PRINT((ndo, " ns:"));
				if ((cp = ns_rprint(ndo, cp, bp, is_mdns)) == NULL)
					goto trunc;
				while (nscount-- && cp < ndo->ndo_snapend) {
					ND_PRINT((ndo, ","));
					if ((cp = ns_rprint(ndo, cp, bp, is_mdns)) == NULL)
						goto trunc;
				}
			}
			if (nscount > 0)
				goto trunc;
			if (cp < ndo->ndo_snapend && arcount--) {
				ND_PRINT((ndo, " ar:"));
				if ((cp = ns_rprint(ndo, cp, bp, is_mdns)) == NULL)
					goto trunc;
				while (cp < ndo->ndo_snapend && arcount--) {
					ND_PRINT((ndo, ","));
					if ((cp = ns_rprint(ndo, cp, bp, is_mdns)) == NULL)
						goto trunc;
				}
			}
			if (arcount > 0)
				goto trunc;
		}
	}
	ND_PRINT((ndo, " (%d)", length));
	return;

  trunc:
	ND_PRINT((ndo, "[|domain]"));
}