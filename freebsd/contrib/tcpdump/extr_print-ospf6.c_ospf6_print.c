#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct ospf6hdr {int ospf6_version; scalar_t__ ospf6_instanceid; scalar_t__ ospf6_areaid; scalar_t__ ospf6_routerid; scalar_t__ ospf6_len; scalar_t__ ospf6_type; } ;
struct TYPE_7__ {int /*<<< orphan*/  ndo_vflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int EXTRACT_16BITS (scalar_t__*) ; 
 scalar_t__ EXTRACT_32BITS (scalar_t__*) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK (scalar_t__) ; 
 int /*<<< orphan*/  ipaddr_string (TYPE_1__*,scalar_t__*) ; 
 int /*<<< orphan*/  ospf6_decode_v3 (TYPE_1__*,struct ospf6hdr const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ospf6_decode_v3_trailer (TYPE_1__*,struct ospf6hdr const*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  ospf6_type_values ; 
 char* tok2str (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  tstr ; 

void
ospf6_print(netdissect_options *ndo,
            register const u_char *bp, register u_int length)
{
	register const struct ospf6hdr *op;
	register const u_char *dataend;
	register const char *cp;
	uint16_t datalen;

	op = (const struct ospf6hdr *)bp;

	/* If the type is valid translate it, or just print the type */
	/* value.  If it's not valid, say so and return */
	ND_TCHECK(op->ospf6_type);
	cp = tok2str(ospf6_type_values, "unknown packet type (%u)", op->ospf6_type);
	ND_PRINT((ndo, "OSPFv%u, %s, length %d", op->ospf6_version, cp, length));
	if (*cp == 'u') {
		return;
	}

	if(!ndo->ndo_vflag) { /* non verbose - so lets bail out here */
		return;
	}

	/* OSPFv3 data always comes first and optional trailing data may follow. */
	ND_TCHECK(op->ospf6_len);
	datalen = EXTRACT_16BITS(&op->ospf6_len);
	if (datalen > length) {
		ND_PRINT((ndo, " [len %d]", datalen));
		return;
	}
	dataend = bp + datalen;

	ND_TCHECK(op->ospf6_routerid);
	ND_PRINT((ndo, "\n\tRouter-ID %s", ipaddr_string(ndo, &op->ospf6_routerid)));

	ND_TCHECK(op->ospf6_areaid);
	if (EXTRACT_32BITS(&op->ospf6_areaid) != 0)
		ND_PRINT((ndo, ", Area %s", ipaddr_string(ndo, &op->ospf6_areaid)));
	else
		ND_PRINT((ndo, ", Backbone Area"));
	ND_TCHECK(op->ospf6_instanceid);
	if (op->ospf6_instanceid)
		ND_PRINT((ndo, ", Instance %u", op->ospf6_instanceid));

	/* Do rest according to version.	 */
	switch (op->ospf6_version) {

	case 3:
		/* ospf version 3 */
		if (ospf6_decode_v3(ndo, op, dataend) ||
		    ospf6_decode_v3_trailer(ndo, op, dataend, length - datalen))
			goto trunc;
		break;
	}			/* end switch on version */

	return;
trunc:
	ND_PRINT((ndo, "%s", tstr));
}