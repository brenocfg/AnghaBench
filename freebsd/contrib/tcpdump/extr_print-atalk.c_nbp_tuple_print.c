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
typedef  scalar_t__ u_short ;
typedef  scalar_t__ u_char ;
struct atNBPtuple {int enumerator; scalar_t__ skt; scalar_t__ node; int /*<<< orphan*/  net; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 scalar_t__ EXTRACT_16BITS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ataddr_string (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 struct atNBPtuple* nbp_name_print (int /*<<< orphan*/ *,struct atNBPtuple const*,scalar_t__ const*) ; 
 int /*<<< orphan*/  tstr ; 

__attribute__((used)) static const struct atNBPtuple *
nbp_tuple_print(netdissect_options *ndo,
                register const struct atNBPtuple *tp, register const u_char *ep,
                register u_short snet, register u_char snode, register u_char skt)
{
	register const struct atNBPtuple *tpn;

	if ((const u_char *)(tp + 1) > ep) {
		ND_PRINT((ndo, "%s", tstr));
		return 0;
	}
	tpn = nbp_name_print(ndo, tp, ep);

	/* if the enumerator isn't 1, print it */
	if (tp->enumerator != 1)
		ND_PRINT((ndo, "(%d)", tp->enumerator));

	/* if the socket doesn't match the src socket, print it */
	if (tp->skt != skt)
		ND_PRINT((ndo, " %d", tp->skt));

	/* if the address doesn't match the src address, it's an anomaly */
	if (EXTRACT_16BITS(&tp->net) != snet || tp->node != snode)
		ND_PRINT((ndo, " [addr=%s]",
		    ataddr_string(ndo, EXTRACT_16BITS(&tp->net), tp->node)));

	return (tpn);
}