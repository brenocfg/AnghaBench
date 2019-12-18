#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct pptp_msg_stopccrq {int reason; int reserved1; int reserved2; } ;
struct TYPE_4__ {scalar_t__ ndo_vflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK (int) ; 
 int /*<<< orphan*/  tstr ; 

__attribute__((used)) static void
pptp_stopccrq_print(netdissect_options *ndo,
                    const u_char *dat)
{
	const struct pptp_msg_stopccrq *ptr = (const struct pptp_msg_stopccrq *)dat;

	ND_TCHECK(ptr->reason);
	ND_PRINT((ndo, " REASON(%u", ptr->reason));
	if (ndo->ndo_vflag) {
		switch (ptr->reason) {
		case 1:
			ND_PRINT((ndo, ":None"));
			break;
		case 2:
			ND_PRINT((ndo, ":Stop-Protocol"));
			break;
		case 3:
			ND_PRINT((ndo, ":Stop-Local-Shutdown"));
			break;
		default:
			ND_PRINT((ndo, ":?"));
			break;
		}
	}
	ND_PRINT((ndo, ")"));
	ND_TCHECK(ptr->reserved1);
	ND_TCHECK(ptr->reserved2);

	return;

trunc:
	ND_PRINT((ndo, "%s", tstr));
}