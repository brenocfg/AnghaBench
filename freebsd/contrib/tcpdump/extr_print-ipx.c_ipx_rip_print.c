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
typedef  int /*<<< orphan*/  u_short ;
typedef  int u_int ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int EXTRACT_16BITS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EXTRACT_32BITS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK (int /*<<< orphan*/  const) ; 

__attribute__((used)) static void
ipx_rip_print(netdissect_options *ndo, const u_short *ipx, u_int length)
{
    int command, i;

    ND_TCHECK(ipx[0]);
    command = EXTRACT_16BITS(ipx);
    ipx++;
    length -= 2;

    switch (command) {
      case 1:
	ND_PRINT((ndo, "ipx-rip-req"));
	if (length > 0) {
	    ND_TCHECK(ipx[3]);
	    ND_PRINT((ndo, " %08x/%d.%d", EXTRACT_32BITS(&ipx[0]),
			 EXTRACT_16BITS(&ipx[2]), EXTRACT_16BITS(&ipx[3])));
	}
	break;
      case 2:
	ND_PRINT((ndo, "ipx-rip-resp"));
	for (i = 0; i < 50 && length > 0; i++) {
	    ND_TCHECK(ipx[3]);
	    ND_PRINT((ndo, " %08x/%d.%d", EXTRACT_32BITS(&ipx[0]),
			 EXTRACT_16BITS(&ipx[2]), EXTRACT_16BITS(&ipx[3])));

	    ipx += 4;
	    length -= 8;
	}
	break;
      default:
	ND_PRINT((ndo, "ipx-rip-?%x", command));
	break;
    }
    return;
trunc:
    ND_PRINT((ndo, "[|ipx %d]", length));
}