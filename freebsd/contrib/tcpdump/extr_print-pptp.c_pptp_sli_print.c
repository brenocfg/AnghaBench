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
typedef  int /*<<< orphan*/  u_char ;
struct pptp_msg_sli {int /*<<< orphan*/  recv_accm; int /*<<< orphan*/  send_accm; int /*<<< orphan*/  reserved1; int /*<<< orphan*/  peer_call_id; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRACT_32BITS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pptp_peer_call_id_print (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tstr ; 

__attribute__((used)) static void
pptp_sli_print(netdissect_options *ndo,
               const u_char *dat)
{
	const struct pptp_msg_sli *ptr = (const struct pptp_msg_sli *)dat;

	ND_TCHECK(ptr->peer_call_id);
	pptp_peer_call_id_print(ndo, &ptr->peer_call_id);
	ND_TCHECK(ptr->reserved1);
	ND_TCHECK(ptr->send_accm);
	ND_PRINT((ndo, " SEND_ACCM(0x%08x)", EXTRACT_32BITS(&ptr->send_accm)));
	ND_TCHECK(ptr->recv_accm);
	ND_PRINT((ndo, " RECV_ACCM(0x%08x)", EXTRACT_32BITS(&ptr->recv_accm)));

	return;

trunc:
	ND_PRINT((ndo, "%s", tstr));
}