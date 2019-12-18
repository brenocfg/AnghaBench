#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
typedef  int u_char ;
struct TYPE_6__ {int ndo_vflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 unsigned int EXTRACT_16BITS (int const*) ; 
 unsigned int MSDP_TYPE_MAX ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK (int const) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int const,int) ; 
 int /*<<< orphan*/  ip_print (TYPE_1__*,int const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipaddr_string (TYPE_1__*,int const*) ; 

void
msdp_print(netdissect_options *ndo, const u_char *sp, u_int length)
{
	unsigned int type, len;

	ND_TCHECK2(*sp, 3);
	/* See if we think we're at the beginning of a compound packet */
	type = *sp;
	len = EXTRACT_16BITS(sp + 1);
	if (len > 1500 || len < 3 || type == 0 || type > MSDP_TYPE_MAX)
		goto trunc;	/* not really truncated, but still not decodable */
	ND_PRINT((ndo, " msdp:"));
	while (length > 0) {
		ND_TCHECK2(*sp, 3);
		type = *sp;
		len = EXTRACT_16BITS(sp + 1);
		if (len > 1400 || ndo->ndo_vflag)
			ND_PRINT((ndo, " [len %u]", len));
		if (len < 3)
			goto trunc;
		sp += 3;
		length -= 3;
		switch (type) {
		case 1:	/* IPv4 Source-Active */
		case 3: /* IPv4 Source-Active Response */
			if (type == 1)
				ND_PRINT((ndo, " SA"));
			else
				ND_PRINT((ndo, " SA-Response"));
			ND_TCHECK(*sp);
			ND_PRINT((ndo, " %u entries", *sp));
			if ((u_int)((*sp * 12) + 8) < len) {
				ND_PRINT((ndo, " [w/data]"));
				if (ndo->ndo_vflag > 1) {
					ND_PRINT((ndo, " "));
					ip_print(ndo, sp + *sp * 12 + 8 - 3,
					         len - (*sp * 12 + 8));
				}
			}
			break;
		case 2:
			ND_PRINT((ndo, " SA-Request"));
			ND_TCHECK2(*sp, 5);
			ND_PRINT((ndo, " for %s", ipaddr_string(ndo, sp + 1)));
			break;
		case 4:
			ND_PRINT((ndo, " Keepalive"));
			if (len != 3)
				ND_PRINT((ndo, "[len=%d] ", len));
			break;
		case 5:
			ND_PRINT((ndo, " Notification"));
			break;
		default:
			ND_PRINT((ndo, " [type=%d len=%d]", type, len));
			break;
		}
		sp += (len - 3);
		length -= (len - 3);
	}
	return;
trunc:
	ND_PRINT((ndo, " [|msdp]"));
}