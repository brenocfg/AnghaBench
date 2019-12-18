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
typedef  scalar_t__ uint16_t ;
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_5__ {int ndo_vflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 scalar_t__ EXTRACT_16BITS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EXTRACT_32BITS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int /*<<< orphan*/  const,scalar_t__ const) ; 
 scalar_t__ OF_PACKET_QUEUE_LEN ; 
 int /*<<< orphan*/  istr ; 
 int /*<<< orphan*/ * of10_queue_props_print (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  tstr ; 

__attribute__((used)) static const u_char *
of10_queues_print(netdissect_options *ndo,
                  const u_char *cp, const u_char *ep, u_int len)
{
	const u_char *cp0 = cp;
	const u_int len0 = len;
	uint16_t desclen;

	while (len) {
		if (len < OF_PACKET_QUEUE_LEN)
			goto invalid;
		/* queue_id */
		ND_TCHECK2(*cp, 4);
		ND_PRINT((ndo, "\n\t  queue_id %u", EXTRACT_32BITS(cp)));
		cp += 4;
		/* len */
		ND_TCHECK2(*cp, 2);
		desclen = EXTRACT_16BITS(cp);
		cp += 2;
		ND_PRINT((ndo, ", len %u", desclen));
		if (desclen < OF_PACKET_QUEUE_LEN || desclen > len)
			goto invalid;
		/* pad */
		ND_TCHECK2(*cp, 2);
		cp += 2;
		/* properties */
		if (ndo->ndo_vflag < 2) {
			ND_TCHECK2(*cp, desclen - OF_PACKET_QUEUE_LEN);
			cp += desclen - OF_PACKET_QUEUE_LEN;
			goto next_queue;
		}
		if (ep == (cp = of10_queue_props_print(ndo, cp, ep, desclen - OF_PACKET_QUEUE_LEN)))
			return ep; /* end of snapshot */
next_queue:
		len -= desclen;
	} /* while */
	return cp;

invalid: /* skip the rest of queues */
	ND_PRINT((ndo, "%s", istr));
	ND_TCHECK2(*cp0, len0);
	return cp0 + len0;
trunc:
	ND_PRINT((ndo, "%s", tstr));
	return ep;
}