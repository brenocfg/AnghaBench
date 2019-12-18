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
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_5__ {int /*<<< orphan*/  ndo_vflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 scalar_t__ rpki_rtr_pdu_print (TYPE_1__*,int /*<<< orphan*/  const*,scalar_t__,int,int) ; 

void
rpki_rtr_print(netdissect_options *ndo, register const u_char *pptr, register u_int len)
{
    if (!ndo->ndo_vflag) {
	ND_PRINT((ndo, ", RPKI-RTR"));
	return;
    }
    while (len) {
	u_int pdu_len = rpki_rtr_pdu_print(ndo, pptr, len, 1, 8);
	len -= pdu_len;
	pptr += pdu_len;
    }
}