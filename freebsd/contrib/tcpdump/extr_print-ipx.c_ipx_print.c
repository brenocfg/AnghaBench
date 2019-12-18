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
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct ipxHdr {int /*<<< orphan*/  length; int /*<<< orphan*/  dstSkt; int /*<<< orphan*/  dstNode; int /*<<< orphan*/  dstNet; int /*<<< orphan*/  srcSkt; int /*<<< orphan*/  srcNode; int /*<<< orphan*/  srcNet; } ;
struct TYPE_5__ {int /*<<< orphan*/  ndo_eflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int EXTRACT_16BITS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EXTRACT_32BITS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK (int /*<<< orphan*/ ) ; 
 int ipxSize ; 
 int /*<<< orphan*/  ipx_decode (TYPE_1__*,struct ipxHdr const*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  ipxaddr_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ipx_print(netdissect_options *ndo, const u_char *p, u_int length)
{
	const struct ipxHdr *ipx = (const struct ipxHdr *)p;

	if (!ndo->ndo_eflag)
		ND_PRINT((ndo, "IPX "));

	ND_TCHECK(ipx->srcSkt);
	ND_PRINT((ndo, "%s.%04x > ",
		     ipxaddr_string(EXTRACT_32BITS(ipx->srcNet), ipx->srcNode),
		     EXTRACT_16BITS(&ipx->srcSkt)));

	ND_PRINT((ndo, "%s.%04x: ",
		     ipxaddr_string(EXTRACT_32BITS(ipx->dstNet), ipx->dstNode),
		     EXTRACT_16BITS(&ipx->dstSkt)));

	/* take length from ipx header */
	ND_TCHECK(ipx->length);
	length = EXTRACT_16BITS(&ipx->length);

	ipx_decode(ndo, ipx, p + ipxSize, length - ipxSize);
	return;
trunc:
	ND_PRINT((ndo, "[|ipx %d]", length));
}