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
typedef  int /*<<< orphan*/  u_short ;
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_6__ {int /*<<< orphan*/  ndo_snapend; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int EXTRACT_16BITS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EXTRACT_32BITS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  fn_printzp (TYPE_1__*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  ipxaddr_string (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ipxsap_string (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ipx_sap_print(netdissect_options *ndo, const u_short *ipx, u_int length)
{
    int command, i;

    ND_TCHECK(ipx[0]);
    command = EXTRACT_16BITS(ipx);
    ipx++;
    length -= 2;

    switch (command) {
      case 1:
      case 3:
	if (command == 1)
	    ND_PRINT((ndo, "ipx-sap-req"));
	else
	    ND_PRINT((ndo, "ipx-sap-nearest-req"));

	ND_TCHECK(ipx[0]);
	ND_PRINT((ndo, " %s", ipxsap_string(ndo, htons(EXTRACT_16BITS(&ipx[0])))));
	break;

      case 2:
      case 4:
	if (command == 2)
	    ND_PRINT((ndo, "ipx-sap-resp"));
	else
	    ND_PRINT((ndo, "ipx-sap-nearest-resp"));

	for (i = 0; i < 8 && length > 0; i++) {
	    ND_TCHECK(ipx[0]);
	    ND_PRINT((ndo, " %s '", ipxsap_string(ndo, htons(EXTRACT_16BITS(&ipx[0])))));
	    if (fn_printzp(ndo, (const u_char *)&ipx[1], 48, ndo->ndo_snapend)) {
		ND_PRINT((ndo, "'"));
		goto trunc;
	    }
	    ND_TCHECK2(ipx[25], 10);
	    ND_PRINT((ndo, "' addr %s",
		ipxaddr_string(EXTRACT_32BITS(&ipx[25]), (const u_char *)&ipx[27])));
	    ipx += 32;
	    length -= 64;
	}
	break;
      default:
	ND_PRINT((ndo, "ipx-sap-?%x", command));
	break;
    }
    return;
trunc:
    ND_PRINT((ndo, "[|ipx %d]", length));
}